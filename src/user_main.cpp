#include "controllers/UserController.h"

int main() {
    UserController controller("data/knowledge_base.json");
    controller.run();
    return 0;
}
