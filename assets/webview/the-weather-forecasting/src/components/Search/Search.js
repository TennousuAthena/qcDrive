import React, { useState, useEffect } from "react";
import { AsyncPaginate } from "react-select-async-paginate";
import { fetchCities } from "../../api/OpenWeatherService";

const defaultCity = {
  value: "41.805699 -123.432777",
  label: "Shenyang, CN",
};

const Search = ({ onSearchChange }) => {
  const [searchValue, setSearchValue] = useState(defaultCity);

  const loadOptions = async (inputValue) => {
    const citiesList = await fetchCities(inputValue);

    return {
      options: citiesList.data.map((city) => {
        return {
          value: `${city.latitude} ${city.longitude}`,
          label: `${city.name}, ${city.countryCode}`,
        };
      }),
    };
  };

  const onChangeHandler = (enteredData) => {
    setSearchValue(enteredData);
    onSearchChange(enteredData);
  };

  useEffect(() => {
    // 组件挂载时，使用默认值进行搜索
    onSearchChange(defaultCity);
  }, []);

  return (
    <AsyncPaginate
      placeholder="Search for cities"
      debounceTimeout={600}
      value={searchValue}
      onChange={onChangeHandler}
      loadOptions={loadOptions}
    />
  );
};

export default Search;
