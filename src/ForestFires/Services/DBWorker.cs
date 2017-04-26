using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using ForestFires.DAL.Context;
using ForestFires.Models;
using Microsoft.Win32.SafeHandles;

namespace ForestFires.Services
{
    public class DBWorker: IDisposable
    {
        private List<Sensor> Sensors { get; set; }
        private readonly SensorsContext _context;
        private bool disposed = false;
        SafeHandle handle = new SafeFileHandle(IntPtr.Zero, true);
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

        public bool UpdateData(int Id, double temperature, double humidity, double smoke,DateTime time, Status status, SensorsContext context)
        {
            //get current Sensor
            var toUpdate = context.Sensors.Find(Id);
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
            context.Entry(toUpdate).CurrentValues.SetValues(updated);
            //save changes
            context.SaveChanges();
            return true;
        }
        public IEnumerable<Sensor> GetSensors()
        {
            foreach (var record in _context.Sensors)
            {
                Sensors.Add(record);
            }
            return Sensors;
        }

        public void Dispose()
        {
           Dispose(true);
           GC.SuppressFinalize(this);
        }
        protected virtual void Dispose(bool disposing)
        {
            if (disposed)
                return;

            if (disposing)
            {
                handle.Dispose();
                // Free any other managed objects here.
                //
            }

            // Free any unmanaged objects here.
            //
            disposed = true;
        }
    }
}
