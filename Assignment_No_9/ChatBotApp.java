import java.util.*;

public class ChatBotApp {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        Map<String, String> responses = new HashMap<>();
        responses.put("hi", "Hello! How can I assist you today?");
        responses.put("hello", "Hi there! How can I help you?");
        responses.put("bye", "Goodbye! Have a great day!");
        responses.put("hours", "We are open from 9 AM to 9 PM, Monday to Saturday.");
        responses.put("location", "We are located at Shivaji Nagar, Pune.");
        responses.put("services", "We provide home delivery and 24x7 customer support.");

        System.out.println("🤖 ChatBot: Hello! Type 'bye' to exit.");

        while (true) {
            System.out.print("You: ");
            String userInput = sc.nextLine().toLowerCase().trim();

            if (userInput.equals("bye")) {
                System.out.println("🤖 ChatBot: " + responses.get("bye"));
                break;
            }

            boolean found = false;
            for (String key : responses.keySet()) {
                if (userInput.contains(key)) {
                    System.out.println("🤖 ChatBot: " + responses.get(key));
                    found = true;
                    break;
                }
            }

            if (!found)
                System.out.println("🤖 ChatBot: Sorry, I didn’t understand that. Can you rephrase?");
        }

        sc.close();
    }
}
