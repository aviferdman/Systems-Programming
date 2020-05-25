package bgu.spl.net.impl.stomp;

import bgu.spl.net.srv.Data.Data;
import bgu.spl.net.srv.Frame;
import bgu.spl.net.srv.Server;
import bgu.spl.net.srv.StompEncDec;
import bgu.spl.net.srv.StompMessagingProtocolImp;

public class StompServer {

    public static void main(String[] args) {
        Data data = Data.getInstance();
        if (args.length > 1) {
            if (args[1].equals("reactor")) {
                Server.reactor(
                        Runtime.getRuntime().availableProcessors(),
                        Integer.parseInt(args[0]), //port
                        () -> new StompMessagingProtocolImp<Frame>(data), //protocol factory
                        StompEncDec::new //message encoder decoder factory
                ).serve();
            } else if (args[1].equals("tpc")){
                Server.threadPerClient(Integer.parseInt(args[0]),
                        () -> new StompMessagingProtocolImp<Frame>(data),
                        StompEncDec::new
                ).serve();
            }
        }
    }
}

