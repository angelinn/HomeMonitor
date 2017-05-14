using System;
using System.Collections.Generic;
using System.Text;

namespace ServiceLayer.DataAccess.Entities
{
    public class Device
    {
        public int Id { get; set; }
        public int DeviceId { get; set; }
        public string LastAddress { get; set; }
        public bool AlarmOn { get; set; }
        public DateTime LastHeartbeat { get; set; }
    }
}
