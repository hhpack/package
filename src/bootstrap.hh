<?hh //strict

/**
 * This file is part of package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace package
{
    type DirectoryPath = string;
    type PackageNamespace = string;
    type SourceFile = string;
    type ClassName = string;
    type Package = shape(
        'namespace' => PackageNamespace,
        'packageDirectory' => DirectoryPath
    );
    type SourceFileVector = ImmVector<SourceFile>;
};
