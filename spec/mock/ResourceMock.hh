<?hh //strict

namespace hhpack\package\spec\mock;

use hhpack\package\NamedObject;

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
