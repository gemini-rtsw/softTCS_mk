%define _prefix /gem_base/epics/ioc
%define name softTCS_mk
%define repository gemdev
%define debug_package %{nil}
%define arch %(uname -m)
%define checkout %(git log --pretty=format:'%h' -n 1) 
%define version 1.0.1
%define git_hash %(git rev-parse --short HEAD 2>/dev/null || echo "nogit")

%global _enable_debug_package 0
%global debug_package %{nil}
%global __os_install_post /usr/lib/rpm/brp-compress %{nil}

Summary: %{name} Package, a module for EPICS base
Name: %{name}
Version: %{version}
Release: 0.git%{git_hash}%{?dist}
License: EPICS Open License
Group: Applications/Engineering
Source0: %{name}-%{version}.tar.gz
ExclusiveArch: %{arch}
Prefix: %{_prefix}

## You may specify dependencies here
BuildRequires: epics-base-devel = 7.0.7-0.git.5fb1f41%{?dist}
BuildRequires: re2c
BuildRequires: tdct
BuildRequires: sequencer-devel = 2.2.9.e5e3615-4.git.7b11f25%{?dist}
BuildRequires: bancomm-devel = 1.6.13-4.git.6f4ba7b%{?dist}
BuildRequires: geminiRec-devel = 4.1.13-3.git.6f58677%{?dist}
BuildRequires: timelib-devel = 2.1.4-3.git.a504360%{?dist}
BuildRequires: slalib-devel = 1.9.7-6.git.54d124d%{?dist}
BuildRequires: gemUtil-devel = 1.6.13-2.git.9268b49%{?dist}
BuildRequires: timeProbe-devel = 1.1.16-3.git.1bb32b7%{?dist}
BuildRequires: pvload-devel = 1.2.1-7.git.6df46ce%{?dist}
BuildRequires: tcslib-devel = 1.1.1-9.git.b18a9b9%{?dist}
BuildRequires: astlib-devel = 1.7.1-8.git.99a7713%{?dist}
BuildRequires: tptlib-devel = 1.1.1-7.git.ec11214%{?dist}
BuildRequires: gemini-ade
Requires: epics-base = 7.0.7-0.git.5fb1f41%{?dist}
Requires: sequencer = 2.2.9.e5e3615-4.git.7b11f25%{?dist}
Requires: autosave
Requires: bancomm = 1.6.13-4.git.6f4ba7b%{?dist}
Requires: geminiRec = 4.1.13-3.git.6f58677%{?dist}
Requires: timelib = 2.1.4-3.git.a504360%{?dist}
Requires: slalib = 1.9.7-6.git.54d124d%{?dist}
Requires: gemUtil = 1.6.13-2.git.9268b49%{?dist}
Requires: timeProbe = 1.1.16-3.git.1bb32b7%{?dist}
Requires: pvload = 1.2.1-7.git.6df46ce%{?dist}
Requires: tcslib = 1.1.1-9.git.b18a9b9%{?dist}
Requires: astlib = 1.7.1-8.git.99a7713%{?dist}
Requires: tptlib = 1.1.1-7.git.ec11214%{?dist}
Requires: procServ
Requires: conserver
Requires: conserver-client

## Switch dependency checking off
AutoReqProv: no

%description
This is the ioc module %{name}.

## If you want to have a devel-package to be generated uncomment the following:
%package devel
Summary: %{name}-devel Package
Group: Development/Gemini
Requires: %{name}
Requires: tdct
Requires: sequencer-devel = 2.2.9.e5e3615-4.git.7b11f25%{?dist}
Requires: bancomm-devel = 1.6.13-4.git.6f4ba7b%{?dist}
Requires: geminiRec-devel = 4.1.13-3.git.6f58677%{?dist}
Requires: timelib-devel = 2.1.4-3.git.a504360%{?dist}
Requires: slalib-devel = 1.9.7-6.git.54d124d%{?dist}
Requires: xycom-devel = 2.1.12-2.git.e8d8b00%{?dist}
Requires: gemUtil-devel = 1.6.13-2.git.9268b49%{?dist}
Requires: timeProbe-devel = 1.1.16-3.git.1bb32b7%{?dist}
Requires: pvload-devel = 1.2.1-7.git.6df46ce%{?dist}
Requires: tcslib-devel = 1.1.1-9.git.b18a9b9%{?dist}
Requires: astlib-devel = 1.7.1-8.git.99a7713%{?dist}
Requires: tptlib-devel = 1.1.1-7.git.ec11214%{?dist}
%description devel
This is the module %{name}.

%prep
%setup -q 

%build
make distclean uninstall
make

%install
export DONT_STRIP=1
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{_prefix}/%{name}
cp -r db $RPM_BUILD_ROOT/%{_prefix}/%{name}
cp -r dbd $RPM_BUILD_ROOT/%{_prefix}/%{name}
cp -r data $RPM_BUILD_ROOT/%{_prefix}/%{name}
cp -r bin $RPM_BUILD_ROOT/%{_prefix}/%{name}
cp -r lib $RPM_BUILD_ROOT/%{_prefix}/%{name}
cp -r include $RPM_BUILD_ROOT/%{_prefix}/%{name}
cp -r configure $RPM_BUILD_ROOT/%{_prefix}/%{name}
find $RPM_BUILD_ROOT/%{_prefix}/%{name}/configure -name ".git" -exec rm -rf {} \;

%post
# register the IOC shared-library dir with the dynamic linker
echo "%{_prefix}/%{name}/lib/linux-x86_64" > /etc/ld.so.conf.d/%{name}.conf
/sbin/ldconfig
# install service file and reload, disable the service
cp -f %{_prefix}/%{name}/data/procserv-%{name}.service /etc/systemd/system/
systemctl daemon-reload
systemctl disable procserv-%{name}.service

%preun
# disable and stop the service before uninstalling
#systemctl disable procserv-%{name}.service
systemctl stop procserv-%{name}.service

%postun
# remove the service file and reload if not upgrading
if [ "$1" == "0" ]; then
    rm -f /etc/systemd/system/procserv-%{name}.service
    systemctl daemon-reload
fi

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
   /%{_prefix}/%{name}/bin
   /%{_prefix}/%{name}/db
   /%{_prefix}/%{name}/dbd
   /%{_prefix}/%{name}/data
   /%{_prefix}/%{name}/lib
   /%{_prefix}/%{name}/configure

%files devel
%defattr(-,root,root)
   /%{_prefix}/%{name}/include

%changelog
* Thu Jun 25 2026 Hawi Stecher <hawi.stecher@noirlab.edu>
- Migrate CI to GitHub Actions (gemini-rtsw-ci)
- Use %{?dist} for dependency pins so EL8 and EL9 both resolve
- Update dependency hashes to match scs_mk; pin epics-base to 7.0.7-0.git.5fb1f41
- Pin xycom-devel; update astlib/tptlib to hashed NVRs
- Add ldconfig setup to RPM %post for libtcs.so
* Fri Jul 19 2024 Anthony Sylvester
- updated to match the CP version, uses new service files without using manage-procs
* Tue Apr 19 2022 Felix Kraemer <felix.kraemer@noirlab.edu> 0.1-33
- some tricks to prevent autostarting softIOCs at boot time
- changes for fixing nsf-noirlab/gemini/rtsw/iocs/softTCS_mk#11
* Wed Mar 02 2022 Matt Rippa <matt.rippa@noirlab.edu> 0.1-32
- New Release merging unstable/2022q1-tr4-nosimspecs branch into TR4

* Tue Mar 01 2022 Matt Rippa <matt.rippa@noirlab.edu> 0.1-31
- All sims configured with 1 RPM

* Sat Feb 26 2022 Matt Rippa <matt.rippa@noirlab.edu> 0.1-30
- Restructure the specfile for simulators

* Thu Feb 24 2022 Matt Rippa <matt.rippa@noirlab.edu> 0.1-29
- Add sim boot files to spec file
- Incorrectly added autosave to the softTCS

* Sat Feb 19 2022 Matt Rippa <matt.rippa@noirlab.edu> 0.1-28
- new package built with tito

* Tue Aug 03 2021 Hawi Stecher 
- Added .gitlab-ci.yml

* Tue Aug 03 2021 Hawi Stecher 
-Containerization changes 

* Tue Apr 13 2021 Felix Kraemer <fkraemer@gemini.edu> 0.1-25
- added gemini-ade to BuildRequires in specfile

* Mon Apr 12 2021 Tiffany Shreves <tiffany.shreves@noirlab.edu> 0.1-24
- Fix TZ environment var from HST 10 to HST10

* Mon Apr 12 2021 Tiffany Shreves <tiffany.shreves@noirlab.edu> 0.1-23
- GS removes not existing GEMS/ECS records
- GS removed disconnected channels

* Thu Apr 01 2021 Tiffany Shreves <tshreves@gemini.edu> 0.1-22
- Integrate gs removed channels updates

* Tue Mar 30 2021 Tiffany Shreves <tshreves@gemini.edu> 0.1-21
- Changes from Roberto and Team South tcsMechOi related

* Tue Mar 02 2021 Tiffany Shreves <tshreves@gemini.edu> 0.1-20
- Comment out xycom check processing line

* Wed Feb 24 2021 Tiffany Shreves <tshreves@gemini.edu> 0.1-19
- Change rtconfig path for softTCS_mk on mkotcsioc-lv2 from tmp to more
  permanent path

* Tue Feb 02 2021 Tiffany Shreves <tshreves@gemini.edu> 0.1-18
- Manage-procs test changing directory path for correct chdir in conf file
- Procserv configuration test adding relative path to spec file manage-procs
  line

* Mon Feb 01 2021 Tiffany Shreves <tshreves@gemini.edu> 0.1-17
- Change top from tc2 to tcs

* Mon Feb 01 2021 Tiffany Shreves <tshreves@gemini.edu> 0.1-16
- Change top to tc1 to test top fix

* Mon Feb 01 2021 Tiffany Shreves <tshreves@gemini.edu> 0.1-15
- Changed top back to tc2 for testing manage-procs change without causing a tcs
  conflict if the change doesn't work as intended

* Mon Feb 01 2021 Tiffany Shreves <tshreves@gemini.edu> 0.1-14
- Change the config_site ttcs from tc2 to tcs to fix the top
- Remove -a flag from spec file manage procs
- Added data to spec

* Tue Jan 26 2021 Tiffany Shreves <tshreves@gemini.edu> 0.1-13
- Change to relative path in boot file and add port to procserv config

* Tue Jan 26 2021 Tiffany Shreves <tshreves@gemini.edu> 0.1-12
- Add conserver-client requirement

* Tue Jan 26 2021 Tiffany Shreves <tshreves@gemini.edu> 0.1-11
- Change configs for mkotcsioc-lv2 tests

* Tue Jan 26 2021 Tiffany Shreves <tshreves@gemini.edu> 0.1-10
- Change the configs for mkotcsioc-lv2 tests
* Fri Jan 22 2021 Tiffany Shreves <tshreves@gemini.edu> 0.1-9
- new package built with tito

* Wed Jan 20 2021 Matt Rippa <mrippa@gemini.edu> 0.1-8
- Fixed build errors due to missing astlib.dbd

* Wed Jan 20 2021 Matt Rippa <mrippa@gemini.edu> 0.1-7
- New Release .6
- New changelog

* Wed Jan 20 2021 Matt Rippa <mrippa@gemini.edu>
- New changelog


