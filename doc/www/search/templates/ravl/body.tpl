<!-- START: body.tpl -->  <body bgcolor="white" text="black" link="blue" vlink="blue" alink="red">    <div align="center">      <a name="top"></a>      <br>      <br>     <table border="0" cellpadding="0" cellspacing="0" width= "450">        <tr>          <td>            <form action="search.php">              <div align="center">                <img src="templates/ravl/images/logo.gif" width= "366" height="97" alt="PHPMySearch">                <br>                <br>              </div>              <div align="center">                <table border="0" cellpadding="0" cellspacing="0"                width="100%">                  <tr>                    <td>                      <div align="left">                        <p align="center"><input type="hidden" name="page" value="1"> <input type=                        "hidden" name="currPath" value="{CURR_PATH}">                         <input type="text" name="search" value="{QUERY}" size="30" maxlength="100" style="background-image: url('templates/ravl/images/bg_input.gif'); bgcolor=#FFFFFF;height:14pt;font-family:arial;font-size:8pt; border: 1 solid #336699;">                         {SELECT_DIR}</p>                        <p align="center"><input type="image" border="0" name="imageField" src="templates/ravl/images/button_search.gif" width="102" height="29" align="middle">                        <br>                        </p>                      </div>                    </td>                  </tr>                  <tr>                    <td align="center">                      <div align="center">                        <font size="2" face= "Arial,Helvetica,Geneva,Swiss,SunSans-Regular">                        <b>Current search location:                        <br>                        </b> {OUT_CURR_PATH}                        <br>                        </font>                      </div>                    </td>                  </tr>                </table>              </div>            </form>          </td>        </tr>      </table>      <br>       {SEARCH_BODY}    </div><!-- END: body.tpl -->