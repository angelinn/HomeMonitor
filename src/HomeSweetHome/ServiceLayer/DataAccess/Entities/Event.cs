using System;
using System.Collections.Generic;
using System.Text;

namespace ServiceLayer.DataAccess.Entities
{
    public class Event
    {
        public int EventId { get; set; }
        public string EventText { get; set; }
        public string Address { get; set; }
        public DateTime Time { get; set; }
    }
}
