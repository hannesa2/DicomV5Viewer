import subprocess

f = open('version.property', 'w')

gitbranch = 'git rev-parse --abbrev-ref HEAD'
gitprocess = subprocess.Popen(gitbranch.split(), stdout=subprocess.PIPE)
branch = gitprocess.stdout.readlines()[0].decode("utf-8").rstrip()

gitid = 'git rev-parse HEAD'
gitprocess = subprocess.Popen(gitid.split(), stdout=subprocess.PIPE)
hash = gitprocess.stdout.readlines()[0].decode("utf-8").rstrip()[0:8]

version = branch
if version == "master":
  version = "5"

if version.count('.') == 0:
  version += ".999"  
if version.count('.') == 1:
  version += ".999"
if version.count('.') == 2:
  version += "." + hash

gitid = 'git rev-parse HEAD'
gitprocess = subprocess.Popen(gitid.split(), stdout=subprocess.PIPE)
release = version + " changeset " + hash

# split the version
version_components = version.split('.')
f.write("short_version = " + version + "\n")
f.write("version = " + release + "\n")
f.write("version_major = " + version_components[0] + "\n")
f.write("version_minor = " + version_components[1] + "\n")
f.write("version_patch = " + version_components[2] + "\n")
f.write("version_build = " + version_components[3] + "\n")
f.close()

print(version_components[0] + '.' + version_components[1] + '.' + version_components[2] + '.' + version_components[3])


