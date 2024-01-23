const x_labels = [];
const y_labels = [];
const press_label = [];
const vel_label = [];

async function getData() {
    try {
        // Fetch data from the local server
        const response = await fetch('Data1.csv');
        const data = await response.text();
        const rows = data.split(/\n/).slice(3);
        rows.forEach(elt => {
            const row = elt.split(',');
            //time,pressure,altitude,velocity,acc_x,acc_y,acc_z,acc_tot
            const time = row[0];
            const alt = row[2];
            const pressure = row[1];
            const vel = row[3];
            //x_labels.push(time);
            console.log("pushed time");
            x_labels.push(time);
            y_labels.push(alt);
            press_label.push(pressure);
            vel_label.push(vel);
            console.log("pushed alt");
            console.log(time, alt);
        });

        if (!response.ok) {
            throw new Error(`Failed to fetch: ${response.status} ${response.statusText}`);
        }

        // Call myChart after successfully fetching data
        Altitude_chart();
        Pressure_chart();
        Velocity_chart();
    } catch (error) {
        console.error('Error fetching data:', error);
        console.error(error.stack);
    }
}

function Altitude_chart() {
    const data1 = {
        labels: x_labels,
        datasets: [{
            label: 'Altitude vs Time',
            data: y_labels,
            fill: false,
            borderColor: 'rgb(255, 255, 255)', // White color for the line
            backgroundColor: 'rgb(0,0,0)',
            tension: 0
        }]
    };

    // Chart configuration
    const config = {
        type: 'line',
        data: data1,
        options: {
            scales: {
                x: {
                    beginAtZero: true,
                    ticks: {
                        color: 'white' // White color for x-axis labels
                    }
                },
                y: {
                    beginAtZero: true,
                    ticks: {
                        color: 'white' // White color for y-axis labels
                    }
                }
            }
        }
    };

    // Get the canvas element and render the chart
    const ctx = document.getElementById('chart').getContext('2d');
    new Chart(ctx, config);

    setInterval(async () => {
        // Fetch new data and update the chart
        await getData();
        myChart.data.labels = x_labels;
        myChart.data.datasets[0].data = y_labels;
        myChart.update();
    }, 5000);
}

function Pressure_chart() {
// Define the data for the chart
const data2 = {
labels: x_labels, // X-axis labels
datasets: [{
    label: 'Pressure vs Time',
    data: press_label,
    fill: false,
    borderColor: 'rgb(255, 255, 255)', // Set the line color to white
    backgroundColor: 'rgb(0, 0, 0)', // Set the background color to black
    tension: 0
}]
};

// Chart configuration
const config = {
type: 'line',
data: data2,
options: {
    scales: {
        x: {
            ticks: {
                color: 'white', // Set X-axis label color to white
            },
        },
        y: {
            ticks: {
                color: 'white', // Set Y-axis label color to white
            },
        },
    },
    animation: {
        duration: 3000, // Animation duration in milliseconds
        easing: 'linear', // Easing function for the animation
    }
    }
};

// Get the canvas element and render the chart
const ctx = document.getElementById('chart2').getContext('2d');
new Chart(ctx, config);


}



function Velocity_chart() {
    const data2 = {
        labels: x_labels,
        datasets: [{
            label: 'Velocity vs Time',
            data: vel_label,
            fill: false,
            borderColor: 'rgb(255, 255, 255)',
            backgroundColor: 'rgb(0,0,0)',
            tension: 0
        }]
    };

    // Chart configuration
    const config = {
        type: 'line',
        data: data2,
        options: {
            scales: {
                x: {
                    beginAtZero: true,
                    ticks: {
                        color: 'white'
                    }
                },
                y: {
                    beginAtZero: true,
                    ticks: {
                        color: 'white'
                    }
                }
            }
        }
    };

    // Get the canvas element and render the chart
    const ctx = document.getElementById('chart3').getContext('2d');
    new Chart(ctx, config);

    setInterval(async () => {
        // Fetch new data and update the chart
        await getData();
        myChart.data.labels = x_labels;
        myChart.data.datasets[0].data = y_labels;
        myChart.update();
    }, 5000);
}

function random_range(min, max) {
    return min + Math.floor(Math.random() * (max - min + 1));
}

window.onload = function () {
    //console.log("here");
    getData();
    const starsContainer = document.querySelector('.stars');

    for (let i = 0; i < 50; i++) {
      const star = document.createElement('div');
      star.classList.add('star');
  
      star.style.setProperty('--star-tail-length', `${random_range(500, 750) / 100}em`);
      star.style.setProperty('--top-offset', `${random_range(0, 10000) / 100}vh`);
      star.style.setProperty('--fall-duration', `${random_range(6000, 12000) / 1000}s`);
      star.style.setProperty('--fall-delay', `${random_range(0, 10000) / 1000}s`);
  
      starsContainer.appendChild(star);
    }
};