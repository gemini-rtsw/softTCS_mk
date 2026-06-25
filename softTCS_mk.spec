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
BuildRequires: epics-base-devel = 7.0.7-0.git.37.9b80a5c
BuildRequires: re2c
BuildRequires: tdct
BuildRequires: sequencer-devel = 2.2.9.e5e3615-4.git.68.cf961a8.el8
BuildRequires: bancomm-devel = 1.6.13-4.git.28.1ca0cb4.el8
BuildRequires: geminiRec-devel = 4.1.13-3.git.53.c94c965.el8
BuildRequires: timelib-devel = 2.1.4-3.git.21.866a01c.el8
BuildRequires: slalib-devel = 1.9.7-6.git.67.7872e05.el8
BuildRequires: gemUtil-devel = 1.6.13-2.git.27.0265e0f.el8
BuildRequires: timeProbe-devel = 1.1.16-3.git.27.7207767.el8
BuildRequires: pvload-devel = 1.2.1-7.git.45.a07ac91.el8
BuildRequires: tcslib-devel = 1.1.1-9.git.37.d589d5e.el8
BuildRequires: astlib-devel = 1.7.1-8.git.20.02db443.el8
BuildRequires: tptlib-devel = 1.1.1-7.git.28.dac2fe3.el8
BuildRequires: gemini-ade
Requires: epics-base = 7.0.7-0.git.37.9b80a5c
Requires: sequencer = 2.2.9.e5e3615-4.git.68.cf961a8.el8
Requires: autosave
Requires: bancomm = 1.6.13-4.git.28.1ca0cb4.el8
Requires: geminiRec = 4.1.13-3.git.53.c94c965.el8
Requires: timelib = 2.1.4-3.git.21.866a01c.el8
Requires: slalib = 1.9.7-6.git.67.7872e05.el8
Requires: gemUtil = 1.6.13-2.git.27.0265e0f.el8
Requires: timeProbe = 1.1.16-3.git.27.7207767.el8
Requires: pvload = 1.2.1-7.git.45.a07ac91.el8
Requires: tcslib = 1.1.1-9.git.37.d589d5e.el8
Requires: astlib = 1.7.1-8.git.20.02db443.el8
Requires: tptlib = 1.1.1-7.git.28.dac2fe3.el8
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
Requires: sequencer-devel = 2.2.9.e5e3615-4.git.68.cf961a8.el8
Requires: bancomm-devel = 1.6.13-4.git.28.1ca0cb4.el8
Requires: geminiRec-devel = 4.1.13-3.git.53.c94c965.el8
Requires: timelib-devel = 2.1.4-3.git.21.866a01c.el8
Requires: slalib-devel = 1.9.7-6.git.67.7872e05.el8
Requires: xycom-devel
Requires: gemUtil-devel = 1.6.13-2.git.27.0265e0f.el8
Requires: timeProbe-devel = 1.1.16-3.git.27.7207767.el8
Requires: pvload-devel = 1.2.1-7.git.45.a07ac91.el8
Requires: tcslib-devel = 1.1.1-9.git.37.d589d5e.el8
Requires: astlib-devel = 1.7.1-8.git.20.02db443.el8
Requires: tptlib-devel = 1.1.1-7.git.28.dac2fe3.el8
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


