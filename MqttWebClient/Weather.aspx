<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Weather.aspx.cs" Inherits="MqttWebClient.Weather" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
       <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/font-awesome/4.1.0/css/font-awesome.min.css" />
  
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
    <link rel="stylesheet" type="text/css" href="Swi.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
</head>
<body>
      <form id="form2" runat="server">            

     <center>
         <asp:Panel ID="Panel1" runat="server" style="margin-top: 0px">
    
                
             </asp:Panel>

         </asp:Panel>

     

           <asp:UpdatePanel runat="server" id="UpdatePanel">
           <ContentTemplate>
               
               </center> 


           <asp:Button runat="server" id="Button1" class="btn btn-info" text="Show status" OnClick="Button1_Click" style="text-align: justify" />
                
           
                <asp:ScriptManager ID="ScriptManager1" runat="server" />
      
 




            <asp:Timer runat="server" id="Timer2" Interval="5000" OnTick="Timer2_Tick"></asp:Timer>

                <br />
               Tempurature 1 :
                <asp:Label ID="Sensor1" runat="server" BackColor="#FFCCFF" />  
                <br>

                Humidity 1 :
               <asp:Label ID="Sensor2" runat="server" BackColor="#66FF33" />

               <br>Light1 :
                <asp:Label ID="Sensor3" runat="server" BackColor="#66FF33" />
              
               <br> rain :
               <asp:Label ID="Sensor4" runat="server" BackColor="#66FF33" />

  
               
            </ContentTemplate>
        </asp:UpdatePanel>
    </form>
        </p>
        </body>
</body>
</html>
