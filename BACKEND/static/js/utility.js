const elements = {}; //useful elements that require me to get value
const cards = {}; // cards to draw charts
const _gasNames = ["CO", "CO2", "AL", "TLN", "NH4", "ACT"];

elements.location = document.querySelector("#location");
elements.refreshRate = document.querySelector("#refreshRate");
//elements.activeGas = document.querySelector("#gas");

cards.CO = document.querySelector("#CO-chart");
cards.CO2 = document.querySelector("#CO2-chart");
cards.AL = document.querySelector("#AL-chart");
cards.TLN = document.querySelector("#TLN-chart");
cards.NH4 = document.querySelector("#NH4-chart");
cards.ACT = document.querySelector("#ACT-chart");

document.charts = {};

function initialize() {
  //TODO getAll locations before rendering
  if (!localStorage.getItem("location"))
    localStorage.setItem("location", "all");
  if (!localStorage.getItem("refreshRate"))
    localStorage.setItem("refreshRate", 30);
  if (!localStorage.getItem("activeGas"))
    localStorage.setItem("activeGas", "all");
  if (!localStorage.getItem("data"))
    localStorage.setItem("data", JSON.stringify([]));

  elements.location.value = localStorage.getItem("location");
  elements.refreshRate.value = localStorage.getItem("refreshRate");
  // elements.activeGas.value = localStorage.getItem("activeGas");
}

function drawGasChart(gasName) {
  const indexes = [],
    gasValues = [],
    temp = [],
    hum = [];

  const gasChart = document.charts[gasName];
  //get gas value from data

  const data = getDataFromStorage();

  data
    .filter((point) => {
      let validPoint = true;
      //Check for location
      //validPoint = elements.location.value == point.location;
      return validPoint;
    })
    .forEach((point) => {
      let date = new Date(point.date);

      indexes.push(date);
      gasValues.push(point[gasName]);
      temp.push(point["temperature"]);
      hum.push(point["humidity"]);
    });

  // console.log(gasName, gasValues, temp, hum);

  gasChart.data.labels = indexes;
  gasChart.data.datasets[0].data = gasValues;
  gasChart.data.datasets[1].data = temp;
  gasChart.data.datasets[2].data = hum;

  gasChart.update();
}

function updateData(data_) {
  saveDataToStorage(data_);
  _gasNames.forEach((gasName) => drawGasChart(gasName));
}

function saveDataToStorage(data) {
  const serializedData = JSON.stringify(data);
  localStorage.setItem("data", serializedData);
}

function getDataFromStorage() {
  return JSON.parse(localStorage.getItem("data"));
}

// TODO act using refresh rate
// change page based on filtering gas

function updateDateTime() {
  const dateTimeElement = document.getElementById("current-date-time");
  const now = new Date();
  const options = {
    weekday: "long",
    year: "numeric",
    month: "long",
    day: "numeric",
    hour: "2-digit",
    minute: "2-digit",
    second: "2-digit",
  };
  dateTimeElement.textContent = now.toLocaleDateString("fr-FR", options);
  setTimeout(updateDateTime, 1000);
}
