import React, { useState, useEffect } from 'react';

const App = () => {
    const [sensorData, setSensorData] = useState({});
    const [alerts, setAlerts] = useState([]);

    useEffect(() => {
        const fetchSensorData = async () => {
            // Replace with your API endpoint to fetch sensor data
            const response = await fetch('/api/sensor-data');
            const data = await response.json();
            setSensorData(data);
        };

        const fetchAlerts = async () => {
            // Replace with your API endpoint to fetch alerts
            const response = await fetch('/api/alerts');
            const data = await response.json();
            setAlerts(data);
        };

        fetchSensorData();
        fetchAlerts();

        const interval = setInterval(() => {
            fetchSensorData();
            fetchAlerts();
        }, 5000); // Fetch data every 5 seconds

        return () => clearInterval(interval);
    }, []);

    return (
        <div>
            <h1>Smart Fire and Gas Detection System Dashboard</h1>
            <h2>Real-time Sensor Data</h2>
            <p>Temperature: {sensorData.temperature} °C</p>
            <p>Gas Level: {sensorData.gasLevel} ppm</p>
            <h2>Alerts</h2>
            {alerts.length > 0 ? (
                <ul>
                    {alerts.map((alert, index) => (
                        <li key={index} style={{ color: alert.severity === 'high' ? 'red' : 'orange' }}>{alert.message}</li>
                    ))}
                </ul>
            ) : (
                <p>No alerts</p>
            )}
        </div>
    );
};

export default App;