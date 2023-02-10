Introduction
=============================

The Standard Operating Procedures (SOP) described in this chapter are meant to be followed
by the developers of the Imebra library during the development process.

Each SOP addresses a different task that occurs during the development of Imebra.

Each time a specific SOP is used to perform a specific task, then a reference to the used
SOP should appear in the library changes log or in the issues tracker.


SOPs
====

.. _NEWSOP_1:

SOP NEWSOP/1: Creating a new SOP
--------------------------------

- Date: 2016-10-01
- Version: 1
- Author: Paolo Brandoli
- Intended audience: SOP writers, QA, developers, auditors

A Standard Operating Procedure (SOP) is identified by its ID which
is composed of a short string specific to each SOP and by the SOP version number.

The SOP string is separated from the SOP version by a forward slash.
For instance, the SOP SOPDEV/2 identifies the version 2 of the SOP SOPDEV.

When a SOP is created, write the following text in RST (Restructured Text) format:

::

    .. _SOPCODE_SOPVERSION:

    SOP SOPCODE/SOPVERSION: SOPTITLE
    --------------------------------

    - Date: YYYY-MM-DD
    - Version: SOPVERSION
    - Author: AUTHORNAME
    - Intended audience: INTENDEDAUDIENCE

    SOPSCOPE

    SOPDESCRIPTION

where:

- SOPCODE must be replaced with a unique string identifier (all uppercase)
- SOPVERSION must be 1
- SOPTITLE is the SOP title
- YYYY-MM-DD is the creation date
- AUTHORNAME is the name of the SOP author
- INTENDEDAUDIENCE is the intended audience for the SOP
- SOPSCOPE is the scope of the SOP
- SOPDESCRIPTION is the full description of the SOP

When linking to other SOPs, use the following form:

::

    :ref:`REFERENCEDSOPCODE_REFERENCEDSOPVERSION`

where:

- REFERENCEDSOPCODE is the code of the referenced SOP
- REFERENCEDSOPVERSION is the version of the referenced SOP


.. _MODSOP_1:

SOP MODSOP/1: Modifying the SOPs
---------------------------------

- Date: 2016-10-01
- Version: 1
- Author: Paolo Brandoli
- Intended audience: SOP writers, QA, developers, auditors

The scope of this SOP is to explain how to modify an existing SOP so that old SOPs are still
correctly visible and linked from other parts of the document.

A Standard Operating Procedure (SOP) is identified by its ID which
is composed of a short string specific to each SOP and by the SOP version number.

The SOP string is separated from the SOP version by a forward
slash.
For instance, the SOP SOPDEV/2 identifies the version 2 of the SOP SOPDEV.

The reason for keeping old SOPs in the documentation is because older SOPs may be
referred in the changes log.

When a SOP is modified, write the following text below the replaced SOP title:

::

    Superseded by :ref:`SOPCODE_NEWSOPVERSION`

where SOPCODE is the SOP unique code and NEWSOPVERSION is the new SOP's version.

Place the new version of the SOP ABOVE the superseded one by following the procedure
described in :ref:`NEWSOP_1`, but MODIFY the new SOPVERSION with the new version number
(version of the superseded version plus one).

In the newer version of the SOP, place the following text under the SOP title:

::

   Replaces :ref:`SOPCODE_SUPERSEDEDSOPVERSION`

where SOPCODE is the SOP unique code and SUPERSEDEDSOPVERSION is the superseded
SOP version

After the SOP has been superseded, look for the string SOPCODE_SUPERSEDEDSOPVERSION
in the documentation and, if appropriate, replace it with the reference to the newer
SOP. If the replacement is done in another SOP, then instead of modifying the SOP replace
it with a new one that superseds the current one (follow this procedure for also for the
other SOP).


.. _BUGUSER_1:

SOP BUGUSER/1: Reporting a bug: instructions for users
-------------------------------------------------------

- Date: 2016-10-01
- Version: 1
- Author: Paolo Brandoli
- Intended audience: bug reporters, library users

The scope of this SOP is to explain to the library users how to report a bug related to the
Imebra library.

Once a bug has been identified, it should be reported on the issue tracker
located at https://bitbucket.org/binarno/imebra/issues.

How to report a bug:

- navigate to the website https://bitbucket.org/binarno/imebra/issues
- click on the button "+ Create issue"
- if you want to be notified when the issue's status changes then you have to login
  with a Bitbucket account. You can create a new account for free
- fill the issue's title with a short description of the bug
- fill the issue's description with a detailed description of the bug.
  In particular, try to describe the following:
  
  - what should happen if the bug didn't exist
  - what happen when the bug is triggered
  - the causes that trigger the bug (specific files, sequence of operations, special hardware, etc)
  - how to reproduce the bug
  - any error message that appears on the screen or is logged into the log files
  
- In the "Kind" field, select "bug"
- Click on "Select files" to attach additional files that may help in the diagnosis.
  DON'T ATTACH ANY FILE THAT HAS NOT BEEN PROPERLY ANONYMIZED: THE ISSUE TRACKER IS PUBLIC
  AND VISIBLE BY ANYONE.
- Click on "Create issue" to submit the issue.
 

.. _BUGDEV_1:

SOP BUGDEV/1: Reporting a bug: instructions for the library developers
-----------------------------------------------------------------------

- Date: 2016-10-01
- Version: 1
- Author: Paolo Brandoli
- Intended audience: developers, QA

The scope of this SOP is to explain to the library developers how to report a bug related to the
Imebra library.

Once a bug has been identified, it should be reported on the issue tracker
located at https://bitbucket.org/binarno/imebra/issues.

How to report a bug:

- navigate to the website https://bitbucket.org/binarno/imebra/issues and login
- click on the button "+ Create issue"
- fill the issue's title with a short description of the bug
- fill the issue's description with a detailed description of the bug.
  In particular, try to describe the following:
  
  - what should happen if the bug didn't exist
  - what happen when the bug is triggered
  - the causes that trigger the bug (specific files, sequence of operations, special hardware, etc)
  - how to reproduce the bug
  - any error message that appears on the screen or is logged into the log files
  
- In the "Kind" field, select "bug"
- In the "Priority" field, select bug priority
- In the "Component" field select the component in which the bug is located
- In the "Version" field select the first released version in which the bug appears
- Click on "Select files" to attach additional files that may help in the diagnosis.
  DON'T ATTACH ANY FILE THAT HAS NOT BEEN PROPERLY ANONYMIZED: THE ISSUE TRACKER IS PUBLIC
  AND VISIBLE BY ANYONE.
- Click on "Create issue" to submit the issue.
 

.. _ACKBUG_1:

SOP ACKBUG/1 Acknowledging a bug report or a feature request
-------------------------------------------------------------

- Date: 2016-10-01
- Version: 1
- Author: Paolo Brandoli
- Intended audience: QA, developers

The scope of this SOP is to record in the issue tracker that a specific bug or feature
has been taken into consideration and somebody is actively working on it.

Once a bug has been reported using :ref:`BUGUSER_1` or :ref:`BUGDEV_1`, then the developer must
acknowledge the bug when he starts working on it.

In order to acknowledge the bug:

- navigate to the website https://bitbucket.org/binarno/imebra/issues and login
- locate the bug that you want to acknowledge and click on it
- click the button "Workflow" on the top right of the webpage
- click "Open"
- fill the Comment field with the known facts about the bug (reproducibility, cause, proposed solution, etc)
- click "Change" to record the acknowledgment


.. _FIXBUG_2:

SOP FIXBUG/2 Fixing a bug
-------------------------

Replaces :ref:`FIXBUG_1`

- Date: 2016-10-23
- Version: 2
- Author: Paolo Brandoli
- Intended audience: QA, developers

The scope of this SOP is to guide the developer through the procedures necessary to fix a bug in Imebra.

This SOP can be executed only after the :ref:`ACKBUG_1` has been executed for the bug being fixed.

- if the bug is specific to a specific branch of Imebra (e.g. 4.0 or 4.1) then switch the active branch
  to the specific branch on the development machine, otherwise switch to the default branch.
- write a test unit that forces the bug to manifest itself and cause the test to fail
- start fixing the bug on the development machine
- all the commits relative to the bugfix must:
  
  - be in a branch named "bugfix_XXX_DDD" where XXX is the bug number in the issue tracker and DDD is a short
    bug description with underscores instead of spaces
  - the commit messages must contain the text "Addresses #XXX_ZZZ" where XXX is the bug number in the issue tracker
    and ZZZ is a description of the changes in the commit
    
- when the bug is resolved then merge the bugfix branch into the one from which it has been forked.
  THE BUG IS RESOLVED WHEN THE SOURCE CODE IS CLEAN, ALL THE TEST UNITS PASS, THE DOCUMENTATION IS UPDATED AND
  THE CHANGES LOG has been updated as per :ref:`CHGLOG_1`.
  The merge commit message must contain the text "Resolves #XXX (DDD)" and "As per SOP FIXBUG_2" where XXX is the bug 
  number in the issue tracker and DDD is a short bug description
- when the bugfix has been released then close the bugfix branch


.. _FIXBUG_1:

SOP FIXBUG/1 Fixing a bug
-------------------------

Superseded by :ref:`FIXBUG_2`

- Date: 2016-10-01
- Version: 1
- Author: Paolo Brandoli
- Intended audience: QA, developers

The scope of this SOP is to guide the developer through the procedures necessary to fix a bug in Imebra.

This SOP can be executed only after the :ref:`ACKBUG_1` has been executed for the bug being fixed.

- if the feature is specific to a specific branch of Imebra (e.g. 4.0 or 4.1) then switch the active branch
  to the specific branch on the development machine, otherwise switch to the master (default) branch.
- write a test unit that forces the bug to manifest itself and cause the test to fail
- start fixing the bug on the development machine
- if the bug needs several commits to be resolved, then every commit related to the bug must be in a 
  branch named "bug_XXX_YYY" where XXX is the bug number in the issue tracker and YYY is a short bug description, 
  with underscore instead of spaces.
  If the bug is resolved in one commit, then the commit can be done directly on the affected branch (master or
  default, 4.0, 4.1, etc).
  THE BUG IS RESOLVED WHEN THE SOURCE CODE IS CLEAN, ALL THE TEST UNITS PASS, THE DOCUMENTATION IS UPDATED
- every commit related to the bug but the last must have the text "Addresses #ZZZ" where ZZZ is the bug number in the
  issue tracker
- the last resolution commit must have the text "Resolves #ZZZ (DDD)" and "As per SOP FIXBUG_XXX" where ZZZ is the bug number in
  the issue tracker, DDD is a short bug description, XXX is the SOP version
- if the bug has been resolved in the dedicated bug branch, then the branch must be merged back to the one from
  which it has been forked.


.. _NEWREQ_1:

SOP NEWREQ/1 Introducing a new requirement
------------------------------------------

- Date: 2016-10-01
- Version: 1
- Author: Paolo Brandoli
- Intended audience: developers, managers

The scope of this SOP is to explain how new requirements have to be introduced.

Requirements are tracked in the xml file docs/imebra_requirements.xml

To introduce a new requirement:

- open the file docs/imebra_requirements.xml in an XML editor
- in the "requirements" tag, create a new "requirement tag" and fill it as per the information
  described in the requirements schema file docs/riskAnalysis.xsd
- save the file

New requirements may introduce new child requirements and cause new risks. New child requirements
must be introduced by following this SOP.

New risks must be added to the docs/imebra_requirements.xml file in the "risks" tag, as described
in the schema file docs/riskAnalysis.xsd. The requirements that mitigate the new risks have to
be introduced using this SOP.

After the imebra_requirements.xml file has been updated, run the internal tool RiskAnalysis to
regenerate the Requirements & Risk report page in RST format, which also appears in the user's manual.


.. _NEWFEAT_1:

SOP NEWFEAT/1 Announcing a new feature
--------------------------------------

- Date: 2016-10-01
- Version: 1
- Author: Paolo Brandoli
- Intended audience: developers, managers

The scope of this SOP is to explain how new features have to be requested or announced.

A new feature is a new library capability that imposes a modification in the library's interface.

New features have to be backed up by a new requirement: to introduce a new requirement follow :ref:`NEWREQ_1`.

After the requirement for the new feature has been introduced, open a new enhancement issue in the
issue tracker at https://bitbucket.org/binarno/imebra/issues.

To open the new enhancement issue:

- navigate to the website https://bitbucket.org/binarno/imebra/issues and login
- click on the button "+ Create issue"
- fill the issue's title with a the text "Requirement #REQ. DDD" where REQ is the requirement ID
  and DDD is the requirement description
- fill the issue's description with a detailed description of the feature.
- In the "Kind" field, select "enhancement"
- In the "Priority" field, select the enhancement priority
- In the "Component" field select the component that the enhancement will affect
- Click on "Create issue" to submit the enhancement.


.. _NEWENH_1:

SOP NEWENH/1 Announcing the enhancement of an existing feature
--------------------------------------------------------------

- Date: 2016-10-01
- Version: 1
- Author: Paolo Brandoli
- Intended audience: developers, managers

The scope of this SOP is to explain how an enhancement has to be requested or announced.

An enhancement is a new library capability that does not cause a modification in the library's interface.

To open the new enhancement issue:

- navigate to the website https://bitbucket.org/binarno/imebra/issues and login
- click on the button "+ Create issue"
- fill the issue's title with a short description of the enhancement
- fill the issue's description with a detailed description of the enhancement.
- In the "Kind" field, select "enhancement"
- In the "Priority" field, select the enhancement priority
- In the "Component" field select the component that the enhancement will affect
- Click on "Create issue" to submit the enhancement.


.. _DEVFEAT_3:

SOP DEVFEAT/3 Implementing a new feature
----------------------------------------

Replaces :ref:`DEVFEAT_2`

- Date: 2019-06-10
- Version: 3
- Author: Paolo Brandoli
- Intended audience: developers

The scope of this SOP is to explain how the developer should act to implement an announced feature.

This SOP can be executed only after the feature has been announced using :ref:`NEWFEAT_1`.

- Switch to the default branch for the version in which the feature will be available 
- start implementing the feature on the development machine
- all the commits relative to the feature must:
  
  - be in a branch named "feature_XXX_DDD" where XXX is the issue number in the issue tracker and DDD is a short
    feature description with underscores instead of spaces OR

  - the commit messages must contain the text "Addresses #XXX_ZZZ" where XXX is the issue number in the issue tracker
    and ZZZ is a description of the changes in the commit
    
- in the docs/imebra_requirements.xml file, find the requirement related to the implemented feature and add the tag
  "implementedIn", in which you must describe which class/methods implement the new feature
- when the feature is resolved then merge the feature branch into the default branch for the version that will include the feature.
  THE FEATURE IS IMPLEMENTED WHEN THE SOURCE CODE IS CLEAN, ALL THE TEST UNITS PASS, THE DOCUMENTATION IS UPDATED AND
  THE CHANGES LOG has been updated as per :ref:`CHGLOG_1`.
  The merge commit message must contain the text "Resolves #XXX (DDD)" and "As per SOP DEVFEAT_3" where XXX is the issue 
  number in the issue tracker and DDD is a short feature description
- when the feature has been released then close the feature branch

.. _DEVFEAT_2:

SOP DEVFEAT/2 Implementing a new feature
----------------------------------------

Replaces :ref:`DEVFEAT_1`

- Date: 2016-10-23
- Version: 2
- Author: Paolo Brandoli
- Intended audience: developers

The scope of this SOP is to explain how the developer should act to implement an announced feature.

This SOP can be executed only after the feature has been announced using :ref:`NEWFEAT_1`.

- Switch to the default branch
- start implementing the feature on the development machine
- all the commits relative to the feature must:
  
  - be in a branch named "feature_XXX_DDD" where XXX is the issue number in the issue tracker and DDD is a short
    feature description with underscores instead of spaces
  - the commit messages must contain the text "Addresses #XXX_ZZZ" where XXX is the issue number in the issue tracker
    and ZZZ is a description of the changes in the commit
    
- in the docs/imebra_requirements.xml file, find the requirement related to the implemented feature and add the tag
  "implementedIn", in which you must describe which class/methods implement the new feature
- when the feature is resolved then merge the feature branch into the default one.
  THE FEATURE IS IMPLEMENTED WHEN THE SOURCE CODE IS CLEAN, ALL THE TEST UNITS PASS, THE DOCUMENTATION IS UPDATED AND
  THE CHANGES LOG has been updated as per :ref:`CHGLOG_1`.
  The merge commit message must contain the text "Resolves #XXX (DDD)" and "As per SOP FIXBUG_2" where XXX is the issue 
  number in the issue tracker and DDD is a short feature description
- when the feature has been released then close the feature branch


.. _DEVFEAT_1:

SOP DEVFEAT/1 Implementing a new feature
----------------------------------------

Superseded by :ref:`DEVFEAT_2`

- Date: 2016-10-01
- Version: 1
- Author: Paolo Brandoli
- Intended audience: developers

The scope of this SOP is to explain how the developer should act to implement an announced feature.

This SOP can be executed only after the feature has been announced using :ref:`NEWFEAT_1`.

- Switch to the default or master/default branch
- start implementing the feature on the development machine
- if the feature needs several commits to be implemented, then every commit related to the feature must be in a 
  branch named "feature_XXX_YYY" where XXX is the issue number in the issue tracker and YYY is a short feature description, 
  with underscore instead of spaces.
  If the feature is implemented in one commit, then the commit can be done directly on the master/default branch
  THE FEATURE IS IMPLEMENTED WHEN THE SOURCE CODE IS CLEAN, ALL THE TEST UNITS PASS, THE DOCUMENTATION IS UPDATED
- every commit related to the feature but the last one must have the text "Addresses #ZZZ" where ZZZ is the issue number in the
  issue tracker
- before committing the last change, update the changes log by following :ref:`CHGLOG_1`
- the last resolution commit must have the text "Resolves #ZZZ (DDD)" and "As per SOP DEVFEAT_XXX" where ZZZ is the issue number in
  the issue tracker, DDD is a short feature description, XXX is the SOP version
- if the feature has been implemented in the dedicated bug branch, then the branch must be merged back to the master/default one
- in the docs/imebra_requirements.xml file, find the requirement related to the implemented feature and add the tag
  "implementedIn", in which you should describe which class/methods implement the new feature


.. _DEVENH_2:

SOP DEVENH/2 Implementing a new enhancement
--------------------------------------------

Replaces :ref:`DEVENH_1`

- Date: 2016-10-23
- Version: 2
- Author: Paolo Brandoli
- Intended audience: developers

The scope of this SOP is to explain how the developer should act to implement an announced enhancement.

This SOP can be executed only after the enhancement has been announced using :ref:`NEWENH_1`.

- Switch to the default or default branch
- start implementing the enhancement
- all the commits relative to the enhancement must:
  
  - be in a branch named "enhancement_XXX_DDD" where XXX is the issue number in the issue tracker and DDD is a short
    enhancement description with underscores instead of spaces
  - the commit messages must contain the text "Addresses #XXX_ZZZ" where XXX is the issue number in the issue tracker
    and ZZZ is a description of the changes in the commit
    
- when the enhancement is complete then merge the enhancement branch into the one from which it has been forked.
  THE ENHANCEMENT IS IMPLEMENTED WHEN THE SOURCE CODE IS CLEAN, ALL THE TEST UNITS PASS, THE DOCUMENTATION IS UPDATED AND
  THE CHANGES LOG has been updated as per :ref:`CHGLOG_1`.
  The merge commit message must contain the text "Resolves #XXX (DDD)" and "As per SOP DEVENH_2" where XXX is the issue
  number in the issue tracker and DDD is a short enhancement description
- when the feature has been released then close the feature branch


.. _DEVENH_1:

SOP DEVENH/1 Implementing a new enhancement
--------------------------------------------

Superseeded by :ref:`DEVENH_2`

- Date: 2016-10-01
- Version: 1
- Author: Paolo Brandoli
- Intended audience: developers

The scope of this SOP is to explain how the developer should act to implement an announced enhancement.

This SOP can be executed only after the enhancement has been announced using :ref:`NEWENH_1`.

- Switch to the default or master/default branch or to a specific minor version branch if the enhancement is specific for a branch
  (e.g. 4.0, 4.1, etc)
- start implementing the enhancement on the development machine
- if the enhancement needs several commits to be implemented, then every commit related to the feature must be in a 
  branch named "enhancement_XXX_YYY" where XXX is the issue number in the issue tracker and YYY is a short enhancement description, 
  with underscore instead of spaces.
  If the enhancement is implemented in one commit, then the commit can be done directly on the master/default branch or in the minor
  version branch
  THE ENHANCEMENT IS IMPLEMENTED WHEN THE SOURCE CODE IS CLEAN, ALL THE TEST UNITS PASS, THE DOCUMENTATION IS UPDATED
- every commit related to the enhancement but the last one must have the text "Addresses #ZZZ" where ZZZ is the issue number in the
  issue tracker
- before committing the last change, update the changes log by following :ref:`CHGLOG_1`
- the last resolution commit must have the text "Resolves #ZZZ (DDD)" and "As per SOP DEVENH_XXX" where ZZZ is the issue number in
  the issue tracker, DDD is a short feature description, XXX is the SOP version
- if the enhancement has been implemented in the dedicated bug branch, then the branch must be merged back to the branch from which
  the fork happened


.. _CHGLOG_1:

SOP CHGLOG/1 Preparing the changelog
------------------------------------

- Date: 2016-10-01
- Version: 1
- Author: Paolo Brandoli
- Intended audience: developers

The scope of this SOP is to explain how to update the changelog that appears in the Imebra's manual.

Open the file docs/changes_log.txt in a text editor.

Step 1
......

If this is the first modification to the changelog since the last Imebra public distribution, then rename the title

::

    Version |release| (this version)

with the actual name of the last Imebra public distribution, otherwise skip to step 2.

For instance, the following text:

::

    Version |release| (this version)
    --------------------------------

    - fixed bug #1 (sample bug)
    - implemented feature #2 (sample feature)

should be modified into

::

    Version 4.0.5
    -------------

    - fixed bug #1 (sample bug)
    - implemented feature #2 (sample feature)

Then above the modified title, insert the changes log for the new release, with the title

::

    Version |release| (this version)

Step 2
......

Below the title

::

    Version |release| (this version)

add the changes that will be committed.
For each changelog line, indicate the SOP procedures used to implement the feature, referencing them with:

::

    :ref:`SOPCODE_SOPVERSION`

where SOPCODE is the code of the followed SOP and SOPVERSION is the SOP version

Example of new changeslog:

::

    Version |release| (this version)
    --------------------------------

    - fixed bug #3 (bug fixed in this release) according to :ref:`FIXBUG_1`
    - implemented feature #4 (feature for this release) according to :ref:`DEVFEAT_1`

    Version 4.0.5
    -------------

    - fixed bug #1 (sample bug)
    - implemented feature #2 (sample feature)

Step 3
......

Save the changes log.

.. _RELEASE_3:

SOP RELEASE/3 Preparation of a new release
------------------------------------------

Replaces :ref:`RELEASE_2`

- Date: 2019-12-07
- Version: 3
- Author: Paolo Brandoli
- Intended audience: developers

The scope of this SOP is to explain how to produce a new public release of Imebra.

A new release can be prepared after features or bugs have been addressed by following :ref:`DEVENH_2`, :ref:`DEVFEAT_3` or :ref:`FIXBUG_2`.

Push the repository to the remote repo (git push --all), then check the Bitbucket Pipelines (https://bitbucket.org/binarno/imebra_git/addon/pipelines/home/)
to see if the build succeeds. If the build fails then fix the code and repeat this SOP.

If the modifications to the library included back-compatible changes to the library's API then:

- from the master branch create a new minor version branch, where the minor version is the current minor version+1 (e.g. 4.5 to 4.6) using `git checkout -b XX.YY`
- perform an empty commit with the message "Opening XX.YY" where XX is the major version and YY is the minor version, using `git commit --allow-empty -m "Opening XX.YY"`
- from the new minor version branch, create a new patch branch XX.YY.0 (e.g. 4.6.0) using `git checkout -b XX.YY.0`
- perform an empty commit with the message "Opening XX.YY.0" using `git commit --allow-empty -m "Opening XX.YY.0"`
- from the new patch branch, create a new build branch XX.YY.0.0 (e.g. 4.6.0.0) using `git checkout -b XX.YY.0.0`
- perform an empty commit with the message "Opening XX.YY.0.0" using `git commit --allow-empty -m "Opening XX.YY.0.0"`
- push the repository to the remote repo using `git push -u --all` and check if the builds succeed (check https://bitbucket.org/binarno/imebra_git/addon/pipelines/home/)

If the modifications to the library didn't modify the library's API but included changes in the library's source code then:

- merge or cherry pick the modifications to the proper minor-version branch
- from the minor version branch, create a new branch with an increased patch number (e.g. 4.5.3 to 4.5.4) using `git checkout -b XX.YY.ZZ` (XX=major, YY=minor, ZZ=patch)
- perform an empty commit with the message "Opening XX.YY.ZZ" using `git commit --allow-empty -m "Opening XX.YY.ZZ"`
- from the new patch branch, create a new build branch XX.YY.0.0 (e.g. 4.6.0.0) using `git checkout -b XX.YY.0.0`
- perform an empty commit with the message "Opening XX.YY.0.0" using `git commit --allow-empty -m "Opening XX.YY.0.0"`
- push the repository to the remote repo using `git push -u --all` and check if the builds succeed (check https://bitbucket.org/binarno/imebra_git/addon/pipelines/home/)

If the modifications to the library didn't involve any source code but only changes to auxiliary files (e.g. documentation, tests, make files, etc) then:

- merge or cherry pick the modifications to the proper minor-version branch and patch branch
  branches (e.g. 4.5 and 4.5.1)
- from the patch branch, create a new build branch XX.YY.ZZ.UU (e.g. 4.6.5.1) using `git checkout -b XX.YY.ZZ.UU` (XX=major, YY=minor, ZZ=patch, UU=build)
- perform an empty commit with the message "Opening XX.YY.ZZ.UU" using `git commit --allow-empty -m "Opening XX.YY.ZZ.UU"`
- push the repository to the remote repo using `git push -u --all` and check if the builds succeed (check https://bitbucket.org/binarno/imebra_git/addon/pipelines/home/)

If the build fails, then fix the code in the proper branch (the branch that where the first modifications were made) and then repeat this SOP.

After the builds succeed:

- upload the build from Dropbox to the Imebra Download Files on Bitbucket (https://bitbucket.org/binarno/imebra_git/downloads).
- on the local repository, switch the branch back to master
- from the master branch, tag the commit used for the build with the actual build number (e.g. 4.5.2.1)
- push the repository to Bitbucket (`git push --tags`)

.. _RELEASE_2:

SOP RELEASE/2 Preparation of a new release
------------------------------------------

Replaces :ref:`RELEASE_1`
Superseeded by :ref:`RELEASE_3`

- Date: 2016-10-23
- Version: 2
- Author: Paolo Brandoli
- Intended audience: developers

The scope of this SOP is to explain how to produce a new public release of Imebra.

A new release can be prepared after features or bugs have been addressed by following :ref:`DEVENH_2`, :ref:`DEVFEAT_2` or :ref:`FIXBUG_2`.

Push the repository to the remote repo (hg push), then check Bitbucket Pipelines (https://bitbucket.org/binarno/imebra_git/addon/pipelines/home/)
to see if the build succeeds. If the build fails then fix the code and repeat this SOP.

If the modifications to the library included back-compatible changes to the library's API then:

- from the master branch create a new minor version branch, where the minor version is the current minor version+1 (e.g. 4.5 to 4.6)
- from the new minor version branch, create a new patch branch (e.g. 4.6.0)
- push the repository to the remote repo (hg push) and check if the builds succeed (check https://bitbucket.org/binarno/imebra_git/addon/pipelines/home/)

If the modifications to the library didn't modify the library's API but included changes in the library's source code then:

- if the modifications were done in the master branch then cherry pick all the modifications and bring them to the proper minor-version
  branches (e.g. 4.5 and/or 4.6)
- from the minor version branch, create a new branch with an increased patch number (e.g. 4.5.3 to 4.5.4)
- push the repository to the remote repo (hg push) and check if the builds succeed (check https://bitbucket.org/binarno/imebra_git/addon/pipelines/home/)

If the modifications to the library didn't involve any source code but only changes to auxiliary files (e.g. documentation, tests, make files, etc) then:

- if the modifications were done in the master branch then cherry pick all the modifications and bring them to the proper minor-version
  branches (e.g. 4.5 and/or 4.6)
- cherry pick the new modifications from the minor version branch (e.g. 4.5 or 4.6) and bring them to the patch branch (e.g. 4.5.4)
- push the repository to the remote repo (hg push) and check if the builds succeed (check https://bitbucket.org/binarno/imebra_git/addon/pipelines/home/)

If the build fails, then fix the code in the proper branch (the branch that where the first modifications were made) and then repeat this SOP.

After the builds succeed:

- upload the build from Dropbox to the Imebra Download Files on Bitbucket (https://bitbucket.org/binarno/imebra/downloads).
- on the local repository, switch the branch back to default
- from the default branch, tag the commit used for the build with the actual build number (e.g. 4.5.2.1)
- push the repository to Bitbucket (hg push)


.. _RELEASE_1:

SOP RELEASE/1 Preparation of a new release
------------------------------------------

Superseeded by :ref:`RELEASE_2`

- Date: 2016-10-01
- Version: 1
- Author: Paolo Brandoli
- Intended audience: developers

The scope of this SOP is to explain how to produce a new public release of Imebra.

A new release can be prepared after features or bugs have been addressed by following :ref:`DEVENH_2`, :ref:`DEVFEAT_2` or :ref:`FIXBUG_2`.

Push the repository to the remote repo (hg push), then check Bitbucket Pipelines (https://bitbucket.org/binarno/imebra_git/addon/pipelines/home/)
to see if the build succeeds. If the build fails then fix the code and repeat this SOP.

If the modifications to the library included back-compatible changes to the library's API then:

- from the master branch create a new minor version branch, where the minor version is the current minor version+1 (e.g. 4.5 to 4.6)
- from the new minor version branch, create a new patch branch (e.g. 4.6.0)
- push the repository to the remote repo (hg push) and check if the builds succeed (check https://bitbucket.org/binarno/imebra_git/addon/pipelines/home/)

If the modifications to the library didn't modify the library's API but included changes in the library's source code then:

- if the modifications were done in the master branch then cherry pick all the modifications and bring them to the proper minor-version
  branches (e.g. 4.5 and/or 4.6)
- from the minor version branch, create a new branch with an increased patch number (e.g. 4.5.3 to 4.5.4)
- push the repository to the remote repo (hg push) and check if the builds succeed (check https://bitbucket.org/binarno/imebra_git/addon/pipelines/home/)

If the modifications to the library didn't involve any source code but only changes to auxiliary files (e.g. documentation, tests, make files, etc) then:

- if the modifications were done in the master branch then cherry pick all the modifications and bring them to the proper minor-version
  branches (e.g. 4.5 and/or 4.6)
- cherry pick the new modifications from the minor version branch (e.g. 4.5 or 4.6) and bring them to the patch branch (e.g. 4.5.4)
- push the repository to the remote repo (hg push) and check if the builds succeed (check https://bitbucket.org/binarno/imebra_git/addon/pipelines/home/)

If the build fails, then fix the code in the proper branch (the branch that where the first modifications were made) and then repeat this SOP.

After the builds succeed:

- upload the build from Dropbox to the Imebra Download Files on Bitbucket (https://bitbucket.org/binarno/imebra/downloads).
- on the local repository, switch the branch back to default
- from the default branch, tag the commit used for the build with the actual build number (e.g. 4.5.2.1)
- push the repository to Bitbucket (hg push)
.. _MAJORVERSION_2:

SOP MAJORVERSION/2 Development of a new major version
-----------------------------------------------------

Replaces :ref:`MAJORVERSION_1`

- Date: 2019-12-07
- Version: 2
- Author: Paolo Brandoli
- Intended audience: developers

The scope of this SOP is to explain how to start the development of a new major version of Imebra (e.g. version 5.x.x or version 6.x.x).

- from the master branch create a new version branch, named "imebra_vX" where X is the major version number

Each modification in the new version must be developed following the :ref:`DEVFEAT_3`

When the new version is ready to be released, then it will become the new master branch:

- create a new branch where the development for the old version will continue, named "imebra_legacy_vY" where Y is the major version which is being replaced:

  - git checkout master
  - git checkout -b imebra_legacy_vY
  - git commit --allow-empty -m "Imebra vY moved to legacy branch"

- move "imebra_vX" to master

  - git checkout imebra_vX
  - git merge --no-ff -s ours master
  - git checkout master
  - git merge --no-ff imebra_vX

- push the repository to Bitbucket

  - git push -u --all


.. _MAJORVERSION_1:

SOP MAJORVERSION/1 Development of a new major version
-----------------------------------------------------
Superseeded by :ref:`MAJORVERSION_2`

- Date: 2019-06-11
- Version: 1
- Author: Paolo Brandoli
- Intended audience: developers

The scope of this SOP is to explain how to start the development of a new major version of Imebra (e.g. version 5.x.x or version 6.x.x).

- from the master branch create a new version branch, named "imebra_vX" where X is the major version number

Each modification in the new version must be developed following the :ref:`DEVFEAT_3`

When the new version is ready to be released, then it will become the new default branch:

- rename the default branch to "imebra_legacy_vY" where Y is the major version which is being replaced:

  - hg update default
  - hg branch "imebra_legacy_vY"
  - hg commit -m "Move Imebra vY to legacy"
  - hg update default
  - hg commit --close-branch -m"Imebra vY moved to legacy branch"

- rename the "imebra_vX" branch to default

  - hg update "imebra_vX"
  - hg branch default
  - hg commit -m "Move Imebra vX to default"
  - hg update "imebra_vX"
  - hg commit --close-branch -m"Imebra vX moved to default branch"

- push the repository to Bitbucket (hg push)

