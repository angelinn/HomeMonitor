using ServiceLayer.DataAccess.Enums;
using System;
using System.Collections.Generic;
using System.Text;

namespace ServiceLayer.DataAccess.Entities
{
    public class Door
    {
        public int Id { get; set; }
        public DoorStatus Status { get; set; }
        public DateTime Timestamp { get; set; }
    }
}
