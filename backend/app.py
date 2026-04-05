from flask import Flask, request, jsonify
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///sensors.db'
db = SQLAlchemy(app)

class SensorData(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    sensor_type = db.Column(db.String(50), nullable=False)
    value = db.Column(db.Float, nullable=False)
    timestamp = db.Column(db.DateTime, default=db.func.current_timestamp())
    status = db.Column(db.String(50), nullable=True)

@app.route('/api/sensor', methods=['POST'])
def receive_sensor_data():
    data = request.json
    new_data = SensorData(sensor_type=data['sensor_type'], value=data['value'], status=data['status'])
    db.session.add(new_data)
    db.session.commit()
    return jsonify({'message': 'Sensor data received'}), 201

@app.route('/api/sensor/status', methods=['GET'])
def get_sensor_status():
    sensors = SensorData.query.all()
    return jsonify([{'sensor_type': s.sensor_type, 'value': s.value, 'status': s.status} for s in sensors])

@app.route('/api/alerts', methods=['GET'])
def get_alerts():
    alerts = SensorData.query.filter(SensorData.status.isnot(None)).all()
    return jsonify([{'sensor_type': a.sensor_type, 'status': a.status} for a in alerts])

if __name__ == '__main__':
    db.create_all() # Create database tables
    app.run(debug=True)