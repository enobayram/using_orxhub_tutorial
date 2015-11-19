Orx Package Repository
======================

This is a repository of orx packages. The packages are contained as branches in this repository and their names start with the prefix `package/`

Installing Packages
-------------------

In any git repository (empty or otherwise), create an `orx_packages` file that contains the name of a package on each line. The names should not contain the `package/` prefix. Then 

Then to install the packages listed in `orx_packages`, use the [package management script](orxpm.sh) at the repository root as:
```
./orxpm.sh <orxhub_repo_url>
```
