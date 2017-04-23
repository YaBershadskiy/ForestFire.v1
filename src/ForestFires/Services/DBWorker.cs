using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using ForestFires.DAL.Context;
using ForestFires.Models;

namespace ForestFires.Services
{
    public class DBWorker
    {
        private List<Sensor> Sensors { get; set; }
        private readonly SensorsContext _context;
        public DBWorker(SensorsContext context)
        {
            _context = context;
            Sensors = new List<Sensor>();
        }
        public void SetDataFromObject(Sensor newSensor)
        {
            _context.Sensors.Add(newSensor);
            _context.SaveChanges();
        }

        public void SetDataFromParams(double latt, double lngt, double temperature, double humidity, double smoke, DateTime dateTime, Status status)
        {
            _context.Sensors.Add(new Sensor(latt,lngt,temperature,humidity,smoke, dateTime,status));
            _context.SaveChanges();
        }

        public void UpdateData(int Id, double temperature, double humidity, double smoke,DateTime time, Status status)
        {
            //get current Sensor
            var toUpdate = _context.Sensors.Find(Id);
            //copy data
            var updated = toUpdate;
            //Update what you need
            updated.Temperature = temperature;
            updated.Humidity = humidity;
            updated.Smoke = smoke;
            updated.Updated = time;
            updated.CurrentStatus = status;
            //rewrite description
            updated.setInfo();
            //update record in DB
            _context.Entry(toUpdate).CurrentValues.SetValues(updated);
            //save changes
            _context.SaveChanges();

        }
        public IEnumerable<Sensor> GetSensors()
        {
            foreach (var record in _context.Sensors)
            {
                Sensors.Add(record);
            }
            return Sensors;
        }

    }
}
