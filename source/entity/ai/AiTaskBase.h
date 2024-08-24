//
// Created by Alienson on 24.8.2024..
//

#ifndef RHYTHM_AITASKBASE_H
#define RHYTHM_AITASKBASE_H


class AiTaskBase {

public:

    virtual ~AiTaskBase() = default;

    [[nodiscard]] virtual bool shouldExecute() = 0;

    [[nodiscard]] virtual bool shouldContinueExecuting() {
        return shouldExecute();
    }

    [[nodiscard]] virtual bool isInterruptible() {
        return true;
    }

    virtual void startExecuting() {}

    virtual void resetTask() {}

    virtual void updateTask() {}

protected:
    AiTaskBase() = default;

};


#endif //RHYTHM_AITASKBASE_H
