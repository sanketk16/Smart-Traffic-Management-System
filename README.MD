# **Smart Traffic Management System (STMS)**

## **Overview**
**Smart Traffic Management System (STMS)** is a comprehensive solution designed to optimize traffic flow and enhance road safety through efficient control and monitoring of traffic lights at multiple intersections. It integrates real-time data handling, backend processing, frontend visualization, and predictive traffic analytics.

## **Components**

STMS consists of four key components:

1. **Backend**: A C program responsible for managing the state of each traffic light.
2. **Frontend**: A web-based dashboard developed in HTML/JavaScript for real-time visualization of traffic light statuses.
3. **Webserver**: A Flask application in Python, serving the frontend and providing an API for traffic light status.
4. **Analytics**: A Python script for predicting traffic patterns, potentially aiding in optimizing traffic light timings.

## **Getting Started**

### **Prerequisites**

- Python 3.x
- Flask (install using `pip install flask`)
- C Compiler (e.g., GCC for Linux)
- Web Browser (e.g., Chrome, Firefox)

### **Installation and Setup**

1. **Backend Compilation**:
   - Navigate to the `backend` directory.
   - Run `make` to compile the C files into an executable.
2. **Webserver Setup**:
   - Navigate to the `webserver` directory.
   - Run `python app.py` to start the Flask server.
3. **Accessing the Frontend**:
   - Open a web browser and visit `http://localhost:5000`.

## **Usage**

- Monitor the status of traffic lights via the frontend dashboard.
- Ensure the backend program is running for real-time control and updates.
- Utilize the analytics script for predictive traffic management insights.

## **Contributing**

Contributions to STMS are welcome. Please follow these steps to contribute:

1. Fork the repository.
2. Create a new feature branch (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a pull request.

## **License**

Distributed under the MIT License. See `LICENSE` file for more information.

Project Link: 
