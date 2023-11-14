# Smart Traffic Management System

## Overview

This Smart Traffic Management System dynamically adjusts traffic light timings based on traffic volume predictions. It consists of three main components:

1. **Traffic Prediction Script (`predict_traffic.py`)**: Generates traffic volume predictions using historical data and an ARIMA model.
2. **Traffic Light Control System (C Program)**: Manages the state of traffic lights and adjusts timings based on the predictions.
3. **Web Dashboard (Flask App and Frontend)**: Displays the current traffic light status and predictions.

## 1. Traffic Prediction Script

### Overview

The script `predict_traffic.py` predicts traffic volumes using an ARIMA (AutoRegressive Integrated Moving Average) model. It's a time series forecasting method that uses historical data to predict future values.

### Implementation

- The script generates simulated historical traffic data (to be replaced with real data for practical applications).
- It uses the `pmdarima` package to find the best ARIMA model parameters and make predictions.
- Predictions are written to `traffic_prediction.txt`, which is read by the Traffic Light Control System.

### Requirements

- Python 3
- `numpy` and `pmdarima` packages

## 2. Traffic Light Control System

### Overview

A C program manages the traffic lights at various intersections. It reads the predicted traffic volumes and adjusts the green light duration accordingly.

### Functionality

- The program initializes the state of each traffic light and periodically updates them based on a timer.
- It reads the latest traffic prediction from `traffic_prediction.txt` and adjusts the green light duration.
- The current state and remaining time of each traffic light are written to `traffic_states.txt`.

### Integration with Prediction Script

- The C program continuously reads `traffic_prediction.txt` to get the latest traffic volume predictions.
- The traffic light timings are adjusted in real-time based on these predictions.

## 3. Web Dashboard

### Overview

A Flask-based web dashboard provides a real-time view of the traffic light states and the current traffic prediction.

### Backend (Flask App)

- The Flask app serves the current state of traffic lights and the latest traffic prediction.
- It reads `traffic_states.txt` for traffic light information and `traffic_prediction.txt` for the prediction value.
- The app provides endpoints (`/status` and `/prediction`) for the frontend to fetch this data.

### Frontend

- The frontend displays the current traffic light status for each intersection and the latest traffic prediction value.
- JavaScript is used to periodically fetch and update this data from the Flask app.
- The layout uses CSS for styling, ensuring that the traffic light status and prediction information are displayed in a user-friendly manner.

## Setup and Running the System

### Traffic Prediction Script

1. Install necessary Python packages: `numpy` and `pmdarima`.
2. Run `predict_traffic.py` to start generating traffic predictions.

### Traffic Light Control System

1. Compile the C program.
2. Run the compiled executable to start managing traffic lights.

### Web Dashboard

1. Navigate to the Flask app directory.
2. Run `flask run` to start the Flask server.
3. Access the dashboard through the provided URL (typically `http://localhost:5000`).

## Testing

- Ensure all components are running simultaneously.
- Observe the traffic light states and prediction updates on the web dashboard.

## Future Enhancements

- Integration with real-time traffic data sources.
- Advanced data analytics for more accurate traffic predictions.
- Implementation of machine learning models for prediction.
