using System;
using System.Collections.Generic;
using System.Text;

namespace ServiceLayer.DataAccess.Entities
{
    public class Measurement
    {
        public int MeasurementId { get; set; }
        public string Sensor { get; set; }
        public double Value { get; set; }
        public DateTime Time { get; set; }
    }
}
