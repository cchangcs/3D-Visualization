using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace WindowsFormsApplication1
{
    class Resource
    {
        private String ID;//资源ID
        private String Type;//资源类型
        private String Begin;//资源开始采集时间
        private String End;//资源结束采集时间
        private double Lon1;//经度1
        private double Lon2;//经度2
        private double Lat1;//纬度1
        private double Lat2;//纬度2

        public Resource(String id, String type, String begin,
            String end, double lon1, double lon2, double lat1, double lat2)
        {
            this.ID = id;
            this.Type = type;
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

        public void SetType(String type)
        {
            this.Type = type;
        }

        public String GetType()
        {
            return this.Type;
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

        public void SetLat2(int lat2)
        {
            this.Lat2 = lat2;
        }

        public double GetLat2()
        {
            return this.Lat2;
        }
    }
}
