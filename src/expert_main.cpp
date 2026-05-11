#include "controllers/ExpertController.h"

int main() {
    ExpertController controller("data/knowledge_base.json");
    controller.run();
    return 0;
}
