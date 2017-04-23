using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace ForestFires.Models
{
    public enum Status { Ok, Fire }
    public class Sensor
    {
        [Key]
        public int Id { get; set; }

        [Required]
        public double Lattitude { get; set; }
        [Required]
        public double Longtitude { get; set; }
        public string Info { get; private set; }
        [Required]
        public double Temperature { get; set; }
        [Required]
        public double Humidity { get; set; }
        [Required]
        public double Smoke { get; set; }
        public DateTime Updated { get; set; }
        public Status CurrentStatus { get; set; }

        public Sensor()
        {
        }

        public Sensor(double lat, double lngt, double temp, double hum, double smoke,DateTime dateTime, Status status)
        {
            Lattitude = lat;
            Longtitude = lngt;
            Temperature = temp;
            Humidity = hum;
            Smoke = smoke;
            Updated = dateTime;
            CurrentStatus = status;
            setInfo();
        }

        public void setInfo()
        {
            Info = "Temperature = " + Temperature.ToString() + "C Humidity " + Humidity.ToString() + "% Smoke " +
                   Smoke.ToString() + "ppm Status "+CurrentStatus.ToString();
        }
    }
}
