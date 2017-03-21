using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;

namespace MqttWebClient
{
    public partial class Dashboard : System.Web.UI.Page
    {
        MqttClient client = new MqttClient("broker.hivemq.com");

        protected void Page_Load(object sender, EventArgs e)
        {
            ConnectToMQTT();
        }

        private void ConnectToMQTT()
        {
            client = new MqttClient("broker.hivemq.com");
            byte code = client.Connect(Guid.NewGuid().ToString());
            ushort msgId = client.Subscribe(new string[] { "keppa", "/iottest" },
            new byte[] { MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE,
                         MqttMsgBase.QOS_LEVEL_AT_LEAST_ONCE });

            client.MqttMsgPublishReceived += client_MqttMsgPublishReceived;

            Sensor1.Text = "0.00";
            Sensor2.Text = "0.00";
            Sensor3.Text = "0.00";
            Sensor4.Text = "0.00";
            Sensor5.Text = "0.00";
            Status.Text = "Hang";

            Session["Temp"] = "0";
            Session["Humi"] = "0";
            Session["Rain"] = "true";
            Session["Light"] = "0";
            Session["HumiClo"] = "0";

            Session["Status"] = "Hang";
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
           
        }

        void client_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e)
        {
            if (e != null)
            {
                if (e.Topic.Equals("keppa"))
                {
                    var msg = Encoding.UTF8.GetString(e.Message);

                    if (msg.Contains(","))
                    {
                        string[] msgArray = msg.Split(',');

                        if (msgArray[0].Equals("Temp"))
                            Session["Temp"] = msgArray[1];

                        if (msgArray[0].Equals("Humi"))
                            Session["Humi"] = msgArray[1];

                        if (msgArray[0].Equals("Light"))
                            Session["Light"] = msgArray[1];

                        if (msgArray[0].Equals("Rain"))
                           Session["Rain"] = msgArray[1];

                        if (msgArray[0].Equals("HumiClo"))
                            Session["HumiClo"] = msgArray[1];
                    }
                }
            }
        }

        protected void Timer2_Tick(object sender, EventArgs e)
        {
            Sensor1.Text = Session["Temp"].ToString();
            Sensor2.Text = Session["Humi"].ToString();
            Sensor4.Text = Session["Light"].ToString();
            Sensor3.Text = Session["Rain"].ToString();
            Sensor5.Text = Session["HumiClo"].ToString();

            //Check for updating new status from sensors values
            checkValue(int.Parse(Session["Humi"].ToString()),
                        int.Parse(Session["HumiClo"].ToString()),
                        int.Parse(Session["Temp"].ToString()),
                        int.Parse(Session["Light"].ToString()),
                        bool.Parse(Session["Rain"].ToString()));
        }
        public void checkValue(int Humi,int HumiClo,int Temp,int Light,bool Rain) {

            if(HumiClo > 30)
            {
                if(Rain == true)
                {
                    Status.Text = "Kept";
                }
                else
                {
                    if (Light > 10000)
                    {

                        if (Temp > 30)
                        {


                            if (Humi > 50)
                            {
                                Status.Text = "Kept";
                            }
                            else {
                                Status.Text = "Hang";
                            }
                        }
                        else {
                            Status.Text = "Kept";
                        }
                    }
                    else {
                        Status.Text = "Kept";

                    }


                }
            }
            else
            {
                Status.Text = "Kept";
            }
          
        }
    }
}