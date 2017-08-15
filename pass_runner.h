#ifndef PASS_RUNNER_H
#define PASS_RUNNER_H

#include <krunner/abstractrunner.h>

class pass_runner : public Plasma::AbstractRunner
{
    Q_OBJECT

public:
    pass_runner(QObject *parent, const QVariantList &args);
    ~pass_runner();

public: // Plasma::AbstractRunner API
    void match(Plasma::RunnerContext &context) override;
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) override;
};

#endif
