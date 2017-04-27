using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ForestFires.Models
{
    public class WeatherData
    {
        /// <summary>
        /// класс-контейнер для хранения полученных данных
        /// </summary>        
        public int AirTemperature { get; set; }
        public double Precipitation { get; set; }
        public double Pressure { get; set; }
        public string WindSpeed { get; set; }

        public string WindDirection { get; set; }
        public string Humidity { get; set; }
        public string City { get; set; }
        public string WeatherType { get; set; }
        public string Date { get; set; }
    }
}
