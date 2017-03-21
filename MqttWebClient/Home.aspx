<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Home.aspx.cs" Inherits="MqttWebClient.Dashboard" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
     <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/font-awesome/4.1.0/css/font-awesome.min.css" />
  
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
    <link rel="stylesheet" type="text/css" href="Swi.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
</head>
<body>
     <nav class="navbar navbar-default navbar-fixed-top">
      <div class="container">
          <div class="buttonHolder">
        <div class="navbar-header">
          <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <a class="navbar-brand" href="#HOME">KEPPA</a>

        </div>
        <div id="navbar" class="navbar-collapse collapse">
          <ul class="nav navbar-nav">
          
          <!--  <li><a href="#weather">WEATHER</a></li> -->
            <li><a href="#setting">SETTING</a></li>



        </div>
      </div>
    </nav>
    <form id="form1" runat="server">        
        <asp:ScriptManager ID="ScriptManager1" runat="server" />
        <asp:UpdatePanel runat="server" id="UpdatePanel">
            <ContentTemplate>
                <br>
                <br>
                <br><center>
                <asp:Image ID="Image1" runat="server" Height="262px" Width="253px" ImageUrl="~/T-Shirt-2-icon.png" />
                <br><center>
                    <br>

                <asp:Timer runat="server" id="Timer2" Interval="5000" OnTick="Timer2_Tick"></asp:Timer>
                <br>
                Tempurature  :
                <asp:Label runat="server" id="Sensor1" BackColor="#FFCCFF" /><br>                             
                Humidity  :
                <asp:Label runat="server" id="Sensor2" BackColor="#66FF33" />   <br>  
                Rain  :
                <asp:Label runat="server" id="Sensor3" BackColor="#FFCCFF" /><br>                             
               light  :
                <asp:Label runat="server" id="Sensor4" BackColor="#66FF33" />   <br> 

                ------------------------------
                ------------------------------
                <br>
                 Humiclothes :
               <asp:Label runat="server" id="Sensor5" BackColor="#66FF33" />   <br> 
         status  :
               <asp:Label runat="server" id="Status" BackColor="#66FF33" />   <br> 
            </ContentTemplate>
        </asp:UpdatePanel>
    </form>
</body>
</html>
