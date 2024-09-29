async function getDataFromBackend(city = "all") {
  const result = (await fetch("/fetch-data?city=" + city)).json();

  return result;
}
