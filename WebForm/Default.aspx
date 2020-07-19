<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>无标题页</title>

    <script type="text/javascript" src="JScript.js"></script>

</head>
<body>
    <form id="form1" runat="server">
    <div>
        <object id="csharpActiveX" classid="clsid:F742E011-3467-4447-B069-C5BF3D148EF8"">
        </object>
        &nbsp;
        <input type="button" onclick="alert(csharpActiveX.showTime());" value="显示当前时间" />
        <input type="button" onclick="alert(csharpActiveX.SayHello('Hello 123'));" value="Say Hello" />
        <input type="button" onclick="alert(csharpActiveX.getKey());" value="Get Key" id="Button2" />
        <asp:Label ID="lbDog" runat="server" Text="Label"></asp:Label>
        <asp:HiddenField ID="hfDog" runat="server" />
        <asp:Button ID="Button1" runat="server" Text="登陆" OnClick="Button1_Click" 
            OnClientClick="setDog(csharpActiveX.getKey())" style="height: 21px" />
        <input id="Button3" type="button" value="button" onclick="setDog(csharpActiveX.getKey())" /></div>
    </form>
</body>
</html>
