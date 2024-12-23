# v2023.01 (2023-01-15)

## Changes

* Add towncrier news fragments and configuration to the developer-tools.
* towncrier: Fix the path for the template in the pipeline
* gitlint: Allow numbers in commit message prefix, such as `ipv6:`.
* cppcheck: Fix support for C language by not forcing C++, as cppcheck can detect language (C or C++) based on file extension and apply language-specific rules accordingly. Add C99 as a standard.
* public-sync: Sync only when run from internal GitLab instance
* autbot: Fix automerge
* mirror: Pull main changes from public GitLab
* clang-format: Enable sorting includes
* autobot: Update LICENSE.MD file
* ci: Create cloud devices dynamically.
* utils: Add a unique ADUGroup tag for created Azure IoT device.
* release: Automate release
* autobot: Skip MRs worked on by developers


This changelog should be read in conjunction with any release notes provided
for a specific release version.
