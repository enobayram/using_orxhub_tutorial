if [ "$#" -eq 1 ]; then
    REMOTE=$1
    mkdir -p .orxpm
    echo $1 > .orxpm/remote
elif [ -f .orxpm/remote ]; then
    REMOTE=$(cat .orxpm/remote)
    echo "Using the previous package repository: $REMOTE"
else
    DEFAULT_REMOTE='https://github.com/orx/orxhub.git'
    echo "Using the default remote: $DEFAULT_REMOTE"
    REMOTE=$DEFAULT_REMOTE
fi

mkdir -p .orxpm/workbench
cd .orxpm/workbench
git init > /dev/null

echo "Updating the local package repository..."
git fetch $REMOTE '+refs/heads/*:refs/heads/orxhub/*'

echo "Resetting the local package repository state..."
git branch -D empty >/dev/null 2>&1
git checkout --orphan empty
git reset --hard
git clean -f -d

echo "Constructing the platform from packages..."
while read PACKAGE; do
    git merge orxhub/package/$PACKAGE
done < ../../orx_packages

echo "Converting the platform to a monolithic commit..."
git branch -D new_platform >/dev/null 2>&1
git checkout --orphan new_platform

if [ -f ../platform ]; then
    PLATFORM=$(cat ../platform)
    echo "The old platform commit was $PLATFORM"
    git fetch ../../
    git reset $PLATFORM
    git add .
fi

echo "Creating the new platform commit..."
git commit -m "$(echo "Creating a new platform with packages:"; cat ../../orx_packages)"
NEW_PLATFORM=$(git rev-parse HEAD)
echo $NEW_PLATFORM > ../platform

cd ../..

echo "Merging the new platform from commit $NEW_PLATFORM"
git fetch .orxpm/workbench new_platform
git merge $NEW_PLATFORM --no-edit


echo "Committing the OrxPM metadata..."
git add orx_packages .orxpm/platform .orxpm/remote

echo $NEW_PLATFORM $(git rev-parse HEAD)

if [ "$NEW_PLATFORM" == "$(git rev-parse HEAD)" ]; then
    git commit -m "OrxPM metadata"
else
    git commit --amend --no-edit
fi
