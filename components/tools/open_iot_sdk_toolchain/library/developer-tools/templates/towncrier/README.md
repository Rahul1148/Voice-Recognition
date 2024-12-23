# Towncrier guideline

### Installing Towncrier

Please refer to https://github.com/twisted/towncrier#readme

### Configuration

The configuration options are found in the 'towncrier.toml' file in the root directory.

### Adding a release change note for your merge request changeset

To create the file for your release change (which must be added as part of any merge request changeset):

```
towncrier create --edit <prefix>.<suffix> --config developer-tools/templates/towncrier/towncrier.toml --dir .
```

Where:

`<prefix>` is the date/time in the following format `'%Y%m%d%H%M'`, this can be obtained in linux by running the date command.

```
date +'%Y%m%d%H%M'
```

The same format can be obtained in windows powershell with the following command:
```
Get-Date -Format "yyyyMMddHHmm"
```

`<suffix>` is currently limited to "change", however this may be expanded in the future.

Note, the --edit flag opens an editor immediately to allow the text for the change to be added.

The text should take the form of a one line summary of the change being added (this could be
as simple as a copy of the anticipated merge request title).

A check is run in the CI against each new merge request to ensure that a news/change file has been added
for this changeset.

### Building the release changelog

To build the changelog section for a new release run the command:
```
towncrier build --version=<version>  --config developer-tools/templates/towncrier/towncrier.toml --dir .
```

Where `<version>` is the SDK release version. E.g. v2022.07

Note, using the --draft flag will display what the new section will look like without actually creating it.

The new changelog section will have the following format:


# v2022.07 (2022-08-23)

## Changes

- Add towncrier news fragments and configuration to the SDK.
- Another changeset summary
- Another changeset summary

New changelog sections are always added to the top of the CHANGELOG.md file.
