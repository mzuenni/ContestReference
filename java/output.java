//gepufferter nicht autoatischer flushender output
PrintWriter out = new PrintWriter(new BufferedWriter(
                  new OutputStreamWriter(new FileOutputStream(
                  FileDescriptor.out), StandardCharsets.UTF_8), 4096));
out.println("blub" + "a" + "b"); //zeile Ausgeben 
out.println(String.format("%d %s", 5, "a")) // wie printf
out.close();//WICHTIG!
