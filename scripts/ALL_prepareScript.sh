#!/bin/bash
#
# Script to prepare the release for VISHNU source code (All modules)
# Author K. Coulomb (kevin.coulomb@sysfera.com)
# Date 18/04/11
#
# 29/08/11 : Add new directory to prepare in the git version of the depot
#            Merge with WS release
# 21/01/13 : use generateAllDocumentation.sh to generate Vishnu docs.
#            Use CMakeLists.txt to retrieve Vishnu version
# 31/01/13 : do not need the external eclipse_1 repository anymore.
#

if [ $# -ne 0 ] && [ $1 -ne 1 ]; then
  echo "Usage: " $0 " <generator_dir>"
  echo " if generator_dir is given, the documentation will be generated"
  exit 1
fi

generateDoc=0
generatorPath=""
if [ $# -ge 1 ]; then
    generateDoc=1
    generatorPath=$1
fi


if [ ! -f copyright ]; then
  echo "Missing copyright file - please start the script in VISHNU root directory"
  exit 1
fi


# Get common functions and variables
source scripts/common.sh

# script to generate all docs
gen_doc_sh=${scriptDir}/generateAllDocumentation.sh


echo "## Preparing VISHNU v${NO_VERSION} ..."



######################################################################
#                             RELEASE                                #
######################################################################
# Create temporary directory
run_cmd rm -rf /tmp/prepaRel
run_cmd mkdir -p /tmp/prepaRel
path=/tmp/prepaRel/vishnu-$NO_VERSION
run_cmd mkdir -p $path

pathrel=deliverables/src

run_cmd mkdir -p deliverables/
remove_files deliverables/*
run_cmd mkdir -p deliverables/src
run_cmd mkdir -p deliverables/doc
run_cmd mkdir -p deliverables/testReports

# create releasepath
releasePath=deliverables/release/vishnu-$NO_VERSION
run_cmd mkdir -p $releasePath

remove_files deliverables/src/*
remove_files deliverables/doc/*
remove_files deliverables/testReports/*


# Generate all documentation
if [ $generateDoc == 1 ]; then
    echo "## Generating documentation"
    run_cmd $gen_doc_sh $generatorPath
else
    echo "## Documentation will not be generated"
fi


# Copy root cmake list, copyright, README, version
copy_file CMakeLists.txt
copy_file ChangeLog
copy_file README
copy_file copyright
copy_file logoSysFera.jpg
copy_file vishnu_version.hpp.in

# Copy doxygen generator
copy_file Doxyfile
copy_file Doxyfile_API

# Copy generated doxygen documentation files
copy_dir doc

# Copy the licence
copy_dir License

# Copy Cmake find files
copy_dir Cmake

# Copy contrib
copy_dir contrib

# Copy core sources
create_dir core
copy_dir core/src core/
copy_dir core/test core/

# Copy sql scripts
create_dir core/database

copy_file core/database/database_\*.sql core/database/
copy_file core/database/postgre_\*.sql core/database/
copy_file core/database/mysql_\*.sql core/database/

# dependency of emf
create_dir core/deps
copy_file core/deps/CMakeLists.txt core/deps/
copy_dir core/deps/emf4cpp core/deps/

# Copy ZMQ files
copy_dir communication



### Documentation html/pdf/docbook
run_cmd mkdir -p $path/core/doc/adminmanual
run_cmd mkdir -p $path/core/doc/usermanual

run_cmd mkdir -p $pathrel/../doc/adminmanual
run_cmd mkdir -p $pathrel/../doc/usermanual

run_cmd cp core/doc/adminmanual/docbook/adminman-gen.docbook $path/core/doc/adminmanual/vishnu-adminman.docbook
run_cmd cp core/doc/adminmanual/docbook/adminman-gen.pdf     $path/core/doc/adminmanual/vishnu-adminman.pdf
run_cmd cp core/doc/adminmanual/docbook/adminman-gen.html    $path/core/doc/adminmanual/vishnu-adminman.html

run_cmd cp core/doc/usermanual/docbook/userman-gen.docbook $path/core/doc/usermanual/vishnu-userman.docbook
run_cmd cp core/doc/usermanual/docbook/userman-gen.pdf     $path/core/doc/usermanual/vishnu-userman.pdf
run_cmd cp core/doc/usermanual/docbook/userman-gen.html    $path/core/doc/usermanual/vishnu-userman.html

run_cmd cp core/doc/adminmanual/docbook/adminman-gen.docbook $pathrel/../doc/adminmanual/vishnu-adminman.docbook
run_cmd cp core/doc/adminmanual/docbook/adminman-gen.pdf     $pathrel/../doc/adminmanual/vishnu-adminman.pdf
run_cmd cp core/doc/adminmanual/docbook/adminman-gen.html    $pathrel/../doc/adminmanual/vishnu-adminman.html

run_cmd cp core/doc/usermanual/docbook/userman-gen.docbook $pathrel/../doc/usermanual/vishnu-userman.docbook
run_cmd cp core/doc/usermanual/docbook/userman-gen.pdf     $pathrel/../doc/usermanual/vishnu-userman.pdf
run_cmd cp core/doc/usermanual/docbook/userman-gen.html    $pathrel/../doc/usermanual/vishnu-userman.html



###############################################################################
#                                     Java API                                #
###############################################################################
create_dir Java
create_dir Java/impl
create_dir Java/impl/VishnuLib

# Getting vishnu jar
copy_dir $vishnuDir/swigAPI/VishnuLib/\* Java/impl/VishnuLib/
copy_file $vishnuDir/swigAPI/generated/swig_output/\*\.java Java/impl/VishnuLib/src/main/java/com/sysfera/vishnu/api/vishnu/internal/


# Regenerating the jar files
cur=$PWD
change_dir $path

# Constructing the 2 jar to send
change_dir Java/impl/VishnuLib

run_cmd mvn clean
run_cmd mvn install

run_cmd cp target/VishnuLib-3.2.1-SNAPSHOT.jar ..
run_cmd cp target/VishnuLib-3.2.1-SNAPSHOT.jar $cur/$pathrel/Java/impl/

change_dir $cur

###############################################################################
#                                    U M S                                    #
###############################################################################
create_dir UMS

# Copy UMS sources
copy_dir UMS/src UMS

# Copy UMS examples
copy_dir UMS/examples UMS

# Copy UMS manpages
create_dir UMS/doc/man
copy_file UMS/doc/man/CMakeLists.txt UMS/doc/man/
copy_dir UMS/doc/man/man1 UMS/doc/man/
copy_dir UMS/doc/man/man3 UMS/doc/man/

# Copy tests
create_dir UMS/test/
copy_dir UMS/test/src UMS/test/

# Copy test reports in release
run_cmd mkdir -p $pathrel/../testReports

copy_rel_file UMS/test/testReports/\*\.pdf ../testReports/
copy_rel_file UMS/test/testReports/\*\.docbook ../testReports/
copy_rel_file UMS/test/testReports/\*\.html ../testReports/

# Copy test plans in release
run_cmd mkdir -p $pathrel/../doc/concept/images
copy_rel_file UMS/test/testPlan/\*\.pdf ../doc/concept/
copy_rel_file UMS/test/testPlan/\*\.docbook ../doc/concept/
copy_rel_file UMS/test/testPlan/\*\.html ../doc/concept/
copy_rel_file UMS/test/testPlan/images/\* ../doc/concept/images

# Copy design in release
copy_rel_file UMS/design/docbook/\*-gen\.pdf ../doc/concept/
copy_rel_file UMS/design/docbook/\*-gen\.docbook ../doc/concept/
copy_rel_file UMS/design/docbook/\*-gen\.html ../doc/concept/
copy_rel_dir UMS/design/docbook/images/png ../doc/concept/images


###############################################################################
#                                    T M S                                    #
###############################################################################
create_dir TMS

# Copy source files
copy_dir TMS/src TMS/

# Copy tests
create_dir TMS/test
copy_dir TMS/test/src TMS/test

# Copy man pages
create_dir TMS/doc/man
copy_file  TMS/doc/man/CMakeLists.txt TMS/doc/man/
copy_dir  TMS/doc/man/man1 TMS/doc/man/
copy_dir  TMS/doc/man/man3 TMS/doc/man/

# Copy tests in release
copy_rel_file TMS/test/testReports/\*\.pdf ../testReports/
copy_rel_file TMS/test/testReports/\*\.docbook ../testReports/
copy_rel_file TMS/test/testReports/\*\.html ../testReports/

# Copy test plans in release
copy_rel_file TMS/test/testPlan/\*\.pdf ../doc/concept/
copy_rel_file TMS/test/testPlan/\*\.docbook ../doc/concept/
copy_rel_file TMS/test/testPlan/\*\.html ../doc/concept/
copy_rel_file TMS/test/testPlan/images/\* ../doc/concept/images

# Copy design in release
copy_rel_file TMS/design/docbook/\*-gen\.pdf ../doc/concept/
copy_rel_file TMS/design/docbook/\*-gen\.docbook ../doc/concept/
copy_rel_file TMS/design/docbook/\*-gen\.html ../doc/concept/
copy_rel_dir TMS/design/docbook/images/png ../doc/concept/images


###############################################################################
#                                    F M S                                    #
###############################################################################
create_dir FMS

# Copy source files
copy_dir FMS/src FMS

# Copy tests
create_dir FMS/test
copy_dir FMS/test/src FMS/test/

# Copy man pages
create_dir FMS/doc/man
copy_file  FMS/doc/man/CMakeLists.txt FMS/doc/man/
copy_dir FMS/doc/man/man1 FMS/doc/man/
copy_dir FMS/doc/man/man3 FMS/doc/man/

# Copy tests in release
copy_rel_file FMS/test/testReports/\*\.pdf ../testReports/
copy_rel_file FMS/test/testReports/\*\.docbook ../testReports/
copy_rel_file FMS/test/testReports/\*\.html ../testReports/

# Copy test plans in release
copy_rel_file FMS/test/testPlan/\*\.pdf ../doc/concept/
copy_rel_file FMS/test/testPlan/\*\.docbook ../doc/concept/
copy_rel_file FMS/test/testPlan/\*\.html ../doc/concept/
copy_rel_file FMS/test/testPlan/images/\* ../doc/concept/images

# Copy design in release
copy_rel_file FMS/design/docbook/\*-gen\.pdf ../doc/concept/
copy_rel_file FMS/design/docbook/\*-gen\.docbook ../doc/concept/
copy_rel_file FMS/design/docbook/\*-gen\.html ../doc/concept/
copy_rel_dir FMS/design/docbook/images/png ../doc/concept/images

###############################################################################
#                                    CORE                                     #
###############################################################################
# Copy design in release
copy_rel_file core/design/docbook/\*\.pdf ../doc/concept/
copy_rel_file core/design/docbook/\*\.docbook ../doc/concept/
copy_rel_file core/design/docbook/\*\.html ../doc/concept/
copy_rel_dir core/design/docbook/images/png ../doc/concept/images


###############################################################################
#                                   SPECIF                                    #
###############################################################################
run_cmd mkdir -p $pathrel/../doc/specif/images
copy_rel_file core/specs/docbook/\*-gen\.pdf ../doc/specif/
copy_rel_file core/specs/docbook/\*-gen\.docbook ../doc/specif/
copy_rel_file core/specs/docbook/\*-gen\.html ../doc/specif/
copy_rel_dir core/specs/docbook/images/png ../doc/specif/images
copy_rel_dir core/specs/docbook/images/svg ../doc/specif/images


###############################################################################
#                                  SWIG API                                   #
###############################################################################
copy_dir swigAPI
 
###############################################################################
#                                 All modules                                 #
###############################################################################

copy_file scripts/setCopyright.sh 

change_dir $path
run_cmd ./setCopyright.sh copyright
remove_files setCopyright.sh
remove_files tmp.txt

change_dir - 
change_dir $pathrel

run_cmd ./setCopyright.sh copyright
remove_files setCopyright.sh
remove_files tmp.txt

change_dir -
change_dir $path

# Remove .project
remove_files UMS/src/utils/emfdata/UMS_Data/.project
remove_files UMS/src/utils/emfdata/UMS_Data/.cproject
remove_files core/deps/emf4cpp/.project
remove_files core/deps/emf4cpp/.cproject

# remove all ~ files
for i in  $(find . -name "*~") ; do
    remove_files $i
done

# remove all bak files
for i in  $(find . -name "*bak") ; do
    remove_files $i
done

# remove all build dir
for i in  $(find . -name "*build") ; do
    remove_files -rf $i
done

change_dir -
change_dir $pathrel

# Remove .project
remove_files UMS/src/utils/emfdata/UMS_Data/.project
remove_files UMS/src/utils/emfdata/UMS_Data/.cproject
remove_files core/deps/emf4cpp/.project
remove_files core/deps/emf4cpp/.cproject

# remove all ~ files
for i in  $(find . -name "*~") ; do
    remove_files $i
done

# remove all bak files
for i in  $(find . -name "*bak") ; do
    remove_files $i
done

# remove all build dir
for i in  $(find . -name "*build") ; do
    remove_files $i
done

change_dir $path
change_dir ..

# Archive to send
run_cmd_noOutput tar -czvf vishnu-${NO_VERSION}.tgz vishnu-$NO_VERSION

# Moving archive in /tmp
run_cmd mv vishnu-${NO_VERSION}.tgz /tmp/

# also copy it in the release directory
change_dir $vishnuDir
run_cmd cp /tmp/vishnu-${NO_VERSION}.tgz ${releasePath}

# tarballs of the doc and tests
change_dir $pathrel
change_dir ..
run_cmd_noOutput tar -czvf ../${releasePath}/vishnu-${NO_VERSION}_doc.tgz doc
run_cmd_noOutput tar -czvf ../${releasePath}/vishnu-${NO_VERSION}_tests.tgz testReports

# Prepare release note
change_dir $vishnuDir
run_cmd cat > ${releasePath}/releaseNotes <<EOF
+--------------------+
| VISHNU ${NO_VERSION} |
+--------------------+

Dependencies: TODO
EOF


# All done
print_exit
