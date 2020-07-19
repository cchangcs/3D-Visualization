using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WindowsFormsApplication1
{
    class Event
    {
        private String ID;//事件ID
        private String Theme;//事件主题
        private String Begin;//事件开始时间
        private String End;//事件结束时间
        private double Lon1;//经度1
        private double Lon2;//经度2
        private double Lat1;//纬度1
        private double Lat2;//纬度2

        public Event(String id, String theme, String begin,
            String end, double lon1, double lon2, double lat1, double lat2)
        {
            this.ID = id;
            this.Theme = theme;
            this.Begin = begin;
            this.End = end;
            this.Lon1 = lon1;
            this.Lon2 = lon2;
            this.Lat1 = lat1;
            this.Lat2 = lat2;
        }

        public void SetID(String id)
        {
            this.ID = id;
        }

        public String GetID()
        {
            return this.ID;
        }

        public void SetTheme(String theme)
        {
            this.Theme = theme;
        }

        public String GetTheme()
        {
            return this.Theme;
        }

        public void SetBegin(String begin)
        {
            this.Begin = begin;
        }
       
        public String GetBegin()
        {
            return this.Begin;
        }

        public void SetEnd(String end)
        {
            this.End = end;
        }

        public String GetEnd()
        {
            return this.End;
        }

        public void SetLon1(double lon1)
        {
            this.Lon1 = lon1;
        }

        public double GetLon1()
        {
            return this.Lon1;
        }
        
        public void SetLon2(double lon2)
        {
            this.Lon2 = lon2;
        }
       
        public double GetLon2()
        {
            return this.Lon2;
        }

        public void SetLat1(double lat1)
        {
            this.Lat1 = lat1;
        }

        public double GetLat1()
        {
            return this.Lat1;
        }

        public void SetLat2(double lat2)
        {
            this.Lat2 = lat2;
        }

        public double GetLat2()
        {
            return this.Lat2;
        }
    }
}
