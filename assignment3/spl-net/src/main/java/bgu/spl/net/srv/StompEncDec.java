package bgu.spl.net.srv;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.srv.ClientFrames.*;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class StompEncDec implements MessageEncoderDecoder <Frame> {

    private byte[] bytes = new byte[1 << 10]; //start with 1k
    private int len = 0;

    @Override
    public Frame decodeNextByte(byte nextByte) {
        if (nextByte == '\u0000') {
            String message = popString();
            return decodeTheWholeString(message);
        }
        pushByte(nextByte);
        return null; //not a line yet
    }

    @Override
    public byte[] encode(Frame message) {
        String s = message.toString();
        return (s + "\u0000").getBytes(); //uses utf8 by default
    }

    private void pushByte(byte nextByte) {
        if (len >= bytes.length) {
            bytes = Arrays.copyOf(bytes, len * 2);
        }
        bytes[len++] = nextByte;
    }

    private String popString() {
        //notice that we explicitly requesting that the string will be decoded from UTF-8
        //this is not actually required as it is the default encoding in java.
        String result = new String(bytes, 0, len, StandardCharsets.UTF_8);
        len = 0;
        return result;
    }

    //decode by key words
    private Frame decodeTheWholeString(String message){
        String[] decodeMessage = message.split("\n");
        int i = 1;
        String line = decodeMessage[1];
        List<String> headers = new ArrayList<String>();
        while (!(line.equals(""))) {
            headers.add(line.split(":")[1]);
            if (i==decodeMessage.length-1){
                break;
            }
            line = decodeMessage[++i];
        }
        String body = "";
        if (!(i==decodeMessage.length-1)){
            body = decodeMessage[++i];
        }
        switch (decodeMessage[0]){
            case "CONNECT": {
                return new Connect(decodeMessage[0], headers, body);
            }
            case "SUBSCRIBE": {
                return new Subscribe(decodeMessage[0], headers, body);
            }
            case "UNSUBSCRIBE": {
                return new Unsubscribe(decodeMessage[0], headers, body);
            }
            case "SEND": {
                String [] splitSpaces = body.split(" ");
                for (int j=0; j<splitSpaces.length; j=j+1){
                    if(splitSpaces[j].equals("added")){
                        return new SendAdd(decodeMessage[0], headers, body);
                    }
                    else if (splitSpaces[j].equals("borrow")){
                        return new SendBorrow(decodeMessage[0], headers, body);
                    }
                    else if (splitSpaces[j].equals("Returning")){
                        return new SendReturning(decodeMessage[0], headers, body);
                    }
                    else if (splitSpaces[j].equals("status")){
                        return new SendStatus(decodeMessage[0], headers, body);
                    }
                    else if (splitSpaces[j].equals("Taking")){
                        return new SendTakingBook(decodeMessage[0], headers, body);
                    }
                    else if (splitSpaces[j].equals("has")&j<splitSpaces.length-1&&!splitSpaces[j+1].equals("added")){
                        return new SendHasBook(decodeMessage[0], headers, body);
                    }
                    else if (splitSpaces[j].contains(":")){
                        return new SendReplyToStatus(decodeMessage[0], headers, body);
                    }
                }
            }
            case "DISCONNECT": {
                return new Disconnect(decodeMessage[0], headers, body);
            }
        }
        return null;
    }
}
