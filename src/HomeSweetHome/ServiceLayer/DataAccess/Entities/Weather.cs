using System;
using System.Collections.Generic;
using System.Text;

namespace ServiceLayer.DataAccess.Entities
{
    public class Weather
    {
        public int Id { get; set; }
        public int Temperature { get; set; }
        public int Humidity { get; set; }
        public DateTime Timestamp { get; set; }
    }
}
