/*
    Copyright 2020, Mitch Curtis

    This file is part of Slate.

    Slate is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Slate is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Slate. If not, see <http://www.gnu.org/licenses/>.
*/

#include "modifyanimationcommand.h"

#include <QLoggingCategory>

#include "animation.h"
#include "layeredimageproject.h"

Q_LOGGING_CATEGORY(lcModifyAnimationCommand, "app.undo.modifyAnimationCommand")

ModifyAnimationCommand::ModifyAnimationCommand(LayeredImageProject *project, Animation *animation,
    const QString &name, int fps, int frameCount, int frameX, int frameY, int frameWidth, int frameHeight, QUndoCommand *parent) :
    QUndoCommand(parent),
    mProject(project),
    mAnimation(animation),
    mIndex(project->animationSystem()->indexOfAnimation(name)),
    mNewName(name),
    mNewFps(fps),
    mNewFrameCount(frameCount),
    mNewFrameX(frameX),
    mNewFrameY(frameY),
    mNewFrameWidth(frameWidth),
    mNewFrameHeight(frameHeight),
    mOldName(animation->name()),
    mOldFps(animation->fps()),
    mOldFrameCount(animation->frameCount()),
    mOldFrameX(animation->frameX()),
    mOldFrameY(animation->frameY()),
    mOldFrameWidth(animation->frameWidth()),
    mOldFrameHeight(animation->frameHeight())

{
    qCDebug(lcModifyAnimationCommand) << "constructed" << this;
}

void ModifyAnimationCommand::undo()
{
    qCDebug(lcModifyAnimationCommand) << "undoing" << this;

    auto animation = mProject->animationSystem()->animationAt(mIndex);
    animation->setName(mOldName);
    animation->setFps(mOldFps);
    animation->setFrameCount(mOldFrameCount);
    animation->setFrameX(mOldFrameX);
    animation->setFrameY(mOldFrameY);
    animation->setFrameWidth(mOldFrameWidth);
    animation->setFrameHeight(mOldFrameHeight);
    emit mProject->animationSystem()->animationModified(mIndex);
}

void ModifyAnimationCommand::redo()
{
    qCDebug(lcModifyAnimationCommand) << "redoing" << this;

    auto animation = mProject->animationSystem()->animationAt(mIndex);
    animation->setName(mNewName);
    animation->setFps(mNewFps);
    animation->setFrameCount(mNewFrameCount);
    animation->setFrameX(mNewFrameX);
    animation->setFrameY(mNewFrameY);
    animation->setFrameWidth(mNewFrameWidth);
    animation->setFrameHeight(mNewFrameHeight);
    emit mProject->animationSystem()->animationModified(mIndex);
}

int ModifyAnimationCommand::id() const
{
    return -1;
}

QDebug operator<<(QDebug debug, const ModifyAnimationCommand *command)
{
    QDebugStateSaver saver(debug);
    if (!command)
        return debug << "ModifyAnimationCommand(0x0)";

    debug.nospace() << "(ModifyAnimationCommand index=" << command->mIndex << ")";
    return debug;
}
