#include "pass_runner.h"

K_EXPORT_PLASMA_RUNNER(pass_runner, pass_runner)

pass_runner::pass_runner(QObject *parent, const QVariantList &args)
    : Plasma::AbstractRunner(parent, args)
{
    setObjectName("pass_runner");
}

pass_runner::~pass_runner()
{
}


void pass_runner::match(Plasma::RunnerContext &context)
{

    const QString term = context.query();
    if (term.length() < 3) {
        return;
    }
    //TODO
}

void pass_runner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context)
    Q_UNUSED(match)
}

#include "pass_runner.moc"
