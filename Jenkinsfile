pipeline
{
    agent any
    stages
    {
        stage('Build')
        {
            steps
            {
                echo "Building project in container..."
                sh '''docker build -t my_builder_image -f Dockerfile.build .'''
            }
        }
        stage('Test') 
        {
            steps 
            {
                echo "Running tests..."
                script 
                {
                    def output = sh(script: "docker run --name my_test_run --rm my_builder_image ./fruit_test", returnStdout: true)
                    echo "Captured test output:\n${output}"
                    writeFile file: "test_output.log", text: output
                }
            }
        }
        stage('Archive logs') 
        {
            steps 
            {
                echo "Archivizing logs..."
                archiveArtifacts artifacts: 'logs/*.log', fingerprint: true
            }
        }
    }
}
