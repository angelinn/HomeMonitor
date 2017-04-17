using System;
using System.Collections.Generic;
using System.Text;

namespace ServiceLayer.DataAccess.Entities
{
    public class Device
    {
        public int DeviceId { get; set; }
        public bool IsOnline { get; set; }
        public string LastAddress { get; set; }
        public DateTime LastHeartbeat { get; set; }
    }
}
