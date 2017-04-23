using System;
using System.Collections.Generic;
using System.Data.Entity.Infrastructure;
using System.Linq;
using System.Threading.Tasks;
using ForestFires.DAL.Context;

namespace ForestFires.DAL
{
    public class SensorsContextFactory: IDbContextFactory<SensorsContext>
    {
        public SensorsContext Create()
        {
            return new SensorsContext("Server=(LocalDB)\\MSSQLLocalDB;Database=SensorsDBv1;Trusted_Connection=True;MultipleActiveResultSets=true");
        }
    }
}
