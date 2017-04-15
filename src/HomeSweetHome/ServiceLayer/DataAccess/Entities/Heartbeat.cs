using System;
using System.Collections.Generic;
using System.Text;

namespace ServiceLayer.DataAccess.Entities
{
    public class Heartbeat
    {
        public int HeartbeatId { get; set; }
        public string Address { get; set; }
        public DateTime Time { get; set; }
    }
}
