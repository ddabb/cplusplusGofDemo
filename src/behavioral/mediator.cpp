#include "behavioral/mediator.h"

namespace design_patterns::behavioral {

void mediator_demo() {
	std::cout << "\n========== Mediator Pattern Demo ==========" << std::endl;
	std::cout << "[Demo] Mediator Pattern: encapsulate communication between objects\n" << std::endl;

	std::unique_ptr<mediator::ConcreteMediator> chatRoom = std::make_unique<mediator::ConcreteMediator>("ChatRoom");

	std::cout << "[Demo] --- Creating Colleagues ---" << std::endl;
	mediator::ConcreteColleague alice(chatRoom.get(), "Alice");
	mediator::ConcreteColleague bob(chatRoom.get(), "Bob");
	mediator::ConcreteColleague charlie(chatRoom.get(), "Charlie");

	std::cout << "\n[Demo] --- Registering Colleagues ---" << std::endl;
	chatRoom->registerColleague("Alice", &alice);
	chatRoom->registerColleague("Bob", &bob);
	chatRoom->registerColleague("Charlie", &charlie);

	std::cout << "\n[Demo] --- Alice sends private message to Bob ---" << std::endl;
	alice.send("Bob", "Hey Bob, how are you?");

	std::cout << "\n[Demo] --- Bob sends private message to Alice ---" << std::endl;
	bob.send("Alice", "Hi Alice, I'm doing great!");

	std::cout << "\n[Demo] --- Charlie broadcasts a message ---" << std::endl;
	chatRoom->broadcastMessage("Charlie", "Hello everyone!");

	std::cout << "\n[Demo] --- Alice sends to non-existent colleague ---" << std::endl;
	alice.send("Dave", "Hello Dave!");

	std::cout << "\n============================================\n" << std::endl;
}

} // namespace design_patterns::behavioral
