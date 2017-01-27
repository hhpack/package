<?hh //strict

namespace HHPack\Package\Test\Mock;

use HHPack\Package\NamedObject;

final class ResourceMock implements NamedObject
{
    public function __construct(
        private string $name
    )
    {
    }
    public function name() : string
    {
        return $this->name;
    }
}
