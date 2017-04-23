using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Threading.Tasks;
using ForestFires.Models;

namespace ForestFires.DAL.Context
{
    public class SensorsContext:DbContext
    {
        public SensorsContext(string connString) : base(connString)
        {
        }
        public DbSet<Sensor> Sensors { get; set; }
    }
}
