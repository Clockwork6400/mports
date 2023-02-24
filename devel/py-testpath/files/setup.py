#!/usr/bin/env python
# setup.py generated by flit for tools that don't yet use PEP 517

from distutils.core import setup

packages = \
['testpath']

package_data = \
{'': ['*']}

extras_require = \
{'test': ['pytest']}

setup(name='testpath',
      version='%%PORTVERSION%%',
      description='Test utilities for code working with files and commands',
      author=None,
      author_email='Jupyter Development Team <jupyter@googlegroups.com>',
      url=None,
      packages=packages,
      package_data=package_data,
      extras_require=extras_require,
      python_requires='>= 3.5',
     )
