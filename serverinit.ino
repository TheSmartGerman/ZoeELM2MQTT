void startServer() {
  server.onNotFound([]() {
    server.send(404, "text/plain", "FileNotFound");
  });
  // handle index with Websocket terminal
  server.on("/", []() {
    // send index.html
    server.send(200, "text/html", "<html> "
"<head> "
"      <script> "
"var connection; "
"var evt; "
"var tm; "
"var running;"
""
"function startSocket() {\n"
"  console.log('Starting connection');\n"
"  connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);\n"
"  connection.onopen = function () {\n"
"    connection.send('Connected on ' + new Date());\n"
"    document.getElementById('indicator').style.backgroundColor = 'green';\n"
"    running = true;\n"
"  };\n"
"  connection.onmessage = function (e) {\n"
"    if (e.data == '__ping__') {\n"
"      clearTimeout(tm);\n"
"      document.getElementById('indicator').style.backgroundColor = 'green';\n"
"    } else {\n"
"      console.log('Server: ' + e.data);\n"
"      var outputText = document.getElementById('serverMsg').value;\n"
"      outputText = e.data + '\\n' + outputText;\n"
"      var lines = outputText.split('\\n');\n"
"      console.log('Number of lines: ' + lines.length);\n"
"      if(lines.length > 200) lines.length = 200;\n"
"      outputText = lines.join('\\n');"
"      document.getElementById('serverMsg').value = outputText;\n"
"      document.getElementById('indicator').style.backgroundColor = 'green';\n"
"    }\n"
"  };\n"
"  connection.onerror = function (error) {\n"
"    console.log('WebSocket Error ', error);"
"    document.getElementById('indicator').style.backgroundColor = 'red';\n"
"  };\n"
"  connection.onclose = function (event) {\n"
"    console.log('Websocket closed, restarting ', event);\n"
"  };\n"
"};\n"
"\n"
"function sendMessage() {\n"
"  var inputText = (document.getElementById('clientMsg').value).toString();\n"
"  console.log('Sending: ' + inputText);\n"
"  connection.send(inputText);\n"
"  document.getElementById('clientMsg').value = '';\n"
"};\n"
"\n"
"function ping() {\n"
"  tm = setTimeout(function () {\n"
"    console.log('Closing connection - ping timeout');\n"
"    document.getElementById('indicator').style.backgroundColor = 'red';\n"
"    if (typeof connection === 'undefined' || connection.readyState == 3) startSocket();\n"

"  }, 1000);\n"
"  connection.send('p');\n"
"};\n"
"evt = setInterval(ping, 2000);\n"
"   </script>\n"
"   </head>\n"
"   <body>\n"
"      <textarea id=serverMsg rows=30 cols=80 readonly></textarea>\n"
"      <br/><br/> \n"
"      <form autocomplete=off target='#' onSubmit='javascript:sendMessage();return false;' method=post>"
"        <input type=text id=clientMsg>"
"        <button type=button onClick='javascript:sendMessage();return false;'>Send</button>"
"      </form>\n"
"      <div id=indicator style='width: 50px; height: 10px; border: 1px solid black; background-color: white;'>\n"
"      <script> document.getElementById('serverMsg').value = ''; //startSocket(); </script>\n"
"   </body></html>");
  });

  server.begin();
  
}
