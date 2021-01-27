%define _prefix /gem_base/epics/ioc
%define name softTCS_mk
%define repository gemdev
%define debug_package %{nil}
%define arch %(uname -m)
%define checkout %(git log --pretty=format:'%h' -n 1) 

#These global defines are added to prevent stripping
# symbols on vxWorks cross-compiled code
# Getting 'strip' to work is probably only needed for
# building a related debug sub-package
#
# But this prevents all the strip warnings
# mrippa 20120202
%global _enable_debug_package 0
%global debug_package %{nil}
%global __os_install_post /usr/lib/rpm/brp-compress %{nil}

Summary: %{name} Package, a module for EPICS base
Name: %{name}
Version: 0.1
Release: 12%{?dist}
License: EPICS Open License
Group: Applications/Engineering
Source0: %{name}-%{version}.tar.gz
ExclusiveArch: %{arch}
Prefix: %{_prefix}
## You may specify dependencies here
BuildRequires: epics-base-devel re2c tdct iocStats-devel sequencer-devel bancomm-devel geminiRec-devel timelib-devel slalib-devel xycom-devel gemUtil-devel timeProbe-devel pvload-devel tcslib-devel astlib-devel tptlib-devel
Requires: epics-base iocStats sequencer autosave bancomm geminiRec timelib slalib xycom gemUtil timeProbe pvload tcslib astlib tptlib sequencer procServ conserver conserver-client
## Switch dependency checking off
AutoReqProv: no

%description
This is the ioc module %{name}.

## If you want to have a devel-package to be generated uncomment the following:
%package devel
Summary: %{name}-devel Package
Group: Development/Gemini
Requires: %{name} tdct iocStats-devel sequencer-devel bancomm-devel geminiRec-devel timelib-devel slalib-devel xycom-devel gemUtil-devel timeProbe-devel pvload-devel tcslib-devel astlib-devel tptlib-devel
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
cp -r bin $RPM_BUILD_ROOT/%{_prefix}/%{name}
cp -r lib $RPM_BUILD_ROOT/%{_prefix}/%{name}
cp -r include $RPM_BUILD_ROOT/%{_prefix}/%{name}
cp -r configure $RPM_BUILD_ROOT/%{_prefix}/%{name}
find $RPM_BUILD_ROOT/%{_prefix}/%{name}/configure -name ".git" -exec rm -rf {} \;

%post
source /etc/profile
# if upgrading, remove old systemd related files
if [ "$1" == "2" ]; then
	manage-procs remove -f %{name}
	manage-procs write-procs-cf
fi
# install systemd files
manage-procs add -f -A -C %{_prefix}/%{name}/bin/linux-x86_64 -e LD_LIBRARY_PATH=$LD_LIBRARY_PATH:%{_prefix}/%{name}/lib/linux-x86_64  -Uroot -Groot %{name} st.cmd
if [ ! -d /etc/conserver ]; then mkdir /etc/conserver ; fi; manage-procs write-procs-cf


%postun
if [ "$1" == "0" ]; then
	manage-procs remove -f %{name}
	manage-procs write-procs-cf
	rm -rf %{_prefix}/%{name}
fi


%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
   /%{_prefix}/%{name}/bin
   /%{_prefix}/%{name}/db
   /%{_prefix}/%{name}/dbd
  # /%{_prefix}/%{name}/data
   /%{_prefix}/%{name}/lib
   #/%{_prefix}/%{name}/include
   /%{_prefix}/%{name}/configure

%files devel
%defattr(-,root,root)
   /%{_prefix}/%{name}/include

%changelog
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



