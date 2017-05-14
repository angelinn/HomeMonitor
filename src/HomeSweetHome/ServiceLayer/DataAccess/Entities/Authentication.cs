using ServiceLayer.DataAccess.Enums;
using System;
using System.Collections.Generic;
using System.Text;

namespace ServiceLayer.DataAccess.Entities
{
    public class Authentication
    {
        public int Id { get; set; }
        public AuthenticationType Type { get; set; }
        public DateTime Timestamp { get; set; }
        public bool Success { get; set; }
    }
}
