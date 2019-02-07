plugins {
    id("org.jetbrains.kotlin.jvm").version("1.3.21")

    // Apply the application plugin to add support for building an application
    application
}

repositories {
    jcenter()
}

dependencies {
    implementation(kotlin("stdlib"))
}

application {
    // Define the main class for the application
    mainClassName = "code.MakePkiPath"
}
