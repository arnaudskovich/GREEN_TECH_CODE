document.addEventListener("DOMContentLoaded", function () {
  let timeout = Number(elements.refreshRate.value);
  let city = elements.location.value;

  // creating charts on page
  document.charts = {
    CO: new Chart(cards.CO, {
      type: "line",
      data: {
        labels: [],
        datasets: [
          {
            label: "gas measurement",
            data: [],
            borderColor: "#50C878",
          },
          {
            label: "temperature",
            data: [],
            yAxisID: "temp",
            type: "bar",
            backgroundColor: "#FF6347",
          },
          {
            label: "humidity",
            data: [],
            yAxisID: "hum",
            backgroundColor: "#ADD8E6",
            type: "bar",
          },
        ],
      },
      tension: 0.1,
      options: {
        scales: {
          x: { display: false },
          y: { display: true },
          temp: {
            display: false,
            suggestedMax: 50,
            beginAtZero: true,
          },
          hum: {
            display: false,
            suggestedMax: 100,
            beginAtZero: true,
          },
        },
      },
    }),
    CO2: new Chart(cards.CO2, {
      type: "line",
      data: {
        labels: [],
        datasets: [
          {
            label: "gas measurement",
            data: [],
            borderColor: "#FFD700",
          },
          {
            label: "temperature",
            data: [],
            yAxisID: "temp",
            type: "bar",
            backgroundColor: "#800000",
          },
          {
            label: "humidity",
            data: [],
            yAxisID: "hum",
            backgroundColor: "#000080",
            type: "bar",
          },
        ],
      },
      tension: 0.1,
      options: {
        scales: {
          x: { display: false },
          y: { display: true },
          temp: {
            display: false,
            suggestedMax: 50,
            beginAtZero: true,
          },
          hum: {
            display: false,
            suggestedMax: 100,
            beginAtZero: true,
          },
        },
      },
    }),
    AL: new Chart(cards.AL, {
      type: "line",
      data: {
        labels: [],
        datasets: [
          {
            label: "gas measurement",
            data: [],
            borderColor: "#555555",
          },
          {
            label: "temperature",
            data: [],
            yAxisID: "temp",
            type: "bar",
            backgroundColor: "#FF6F61",
          },
          {
            label: "humidity",
            data: [],
            yAxisID: "hum",
            backgroundColor: "#B0E0E6",
            type: "bar",
          },
        ],
      },
      tension: 0.1,
      options: {
        scales: {
          x: { display: false },
          y: { display: true },
          temp: {
            display: false,
            suggestedMax: 50,
            beginAtZero: true,
          },
          hum: {
            display: false,
            suggestedMax: 100,
            beginAtZero: true,
          },
        },
      },
    }),
    TLN: new Chart(cards.TLN, {
      type: "line",
      data: {
        labels: [],
        datasets: [
          {
            label: "gas measurement",
            data: [],
            borderColor: "#FFA07A",
          },
          {
            label: "temperature",
            data: [],
            yAxisID: "temp",
            type: "bar",
            backgroundColor: "#DC143C",
          },
          {
            label: "humidity",
            data: [],
            yAxisID: "hum",
            backgroundColor: "#007FFF",
            type: "bar",
          },
        ],
      },
      tension: 0.1,
      options: {
        scales: {
          x: { display: false },
          y: { display: true },
          temp: {
            display: false,
            suggestedMax: 50,
            beginAtZero: true,
          },
          hum: {
            display: false,
            suggestedMax: 100,
            beginAtZero: true,
          },
        },
      },
    }),
    NH4: new Chart(cards.NH4, {
      type: "line",
      data: {
        labels: [],
        datasets: [
          {
            label: "gas measurement",
            data: [],
            borderColor: "#C0C0C0",
          },
          {
            label: "temperature",
            data: [],
            yAxisID: "temp",
            type: "bar",
            backgroundColor: "#9B111E",
          },
          {
            label: "humidity",
            data: [],
            yAxisID: "hum",
            backgroundColor: "#87CEEB",
            type: "bar",
          },
        ],
      },
      tension: 0.1,
      options: {
        scales: {
          x: { display: false },
          y: { display: true },
          temp: {
            display: false,
            suggestedMax: 50,
            beginAtZero: true,
          },
          hum: {
            display: false,
            suggestedMax: 100,
            beginAtZero: true,
          },
        },
      },
    }),
    ACT: new Chart(cards.ACT, {
      type: "line",
      data: {
        labels: [],
        datasets: [
          {
            label: "gas measurement",
            data: [],
            borderColor: "#333",
          },
          {
            label: "temperature",
            data: [],
            yAxisID: "temp",
            type: "bar",
            backgroundColor: "#f02126",
          },
          {
            label: "humidity",
            data: [],
            yAxisID: "hum",
            backgroundColor: "#206fff",
            type: "bar",
          },
        ],
      },
      tension: 0.1,
      options: {
        scales: {
          x: { display: false },
          y: { display: true },
          temp: {
            display: false,
            suggestedMax: 50,
            beginAtZero: true,
          },
          hum: {
            display: false,
            suggestedMax: 100,
            beginAtZero: true,
          },
        },
      },
    }),
  };

  //temporized fetcher
  const temporizedFetcher = () => {
    getDataFromBackend(city)
      .then((result) => {
        updateData(result);
      })
      .catch((err) => console.error(err))
      .finally(() => setTimeout(temporizedFetcher, timeout));
  };

  initialize();

  //initial data fetch
  temporizedFetcher();

  elements.refreshRate.addEventListener("change", (e) => {
    console.log(timeout, "before");

    timeout = Number(e.target.value);
    console.log(timeout, "after");
  });

  elements.location.addEventListener("change", (e) => {
    console.log(city, "before");

    city = e.target.value;

    console.log(city, "after");
  });

  //Update time in banner
  updateDateTime();
});
